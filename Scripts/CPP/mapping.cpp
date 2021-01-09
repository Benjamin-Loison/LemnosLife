#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include <map>
#include <sys/types.h>
#include <dirent.h>
#include <tgmath.h>
#include <sys/time.h>
#include <thread>
//#include <atomic>
#include <mutex>
#include <algorithm>
#include <sys/stat.h>

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>

#include "vector2D.h"
#include "vector3D.h"
#include "utils.h"

#define UNSIGNED_INT_MAX 4294967295

#define CST_T true
#define CST_F false

#define CST_T_STR '#'
#define CST_F_STR '.'

#define PI 3.14159265359

using namespace std;

// this code is an adaptation of hardcore parts of mapping.py

//typedef struct Picture Picture;
typedef struct Picture
{
    bool** pic;
    unsigned int h, w;
};

template<typename T>
string convertNbToStr(const T& number)
{
    std::ostringstream convert;
    convert << number;
    return convert.str();
}

template <typename T>
string to_string_with_precision(const T a_value, const int n = 6)
{
    ostringstream out;
    out.precision(n);
    out << fixed << a_value;
    return out.str();
}

vector<string> getFileContent(string path), slice(vector<string> parts, unsigned int i, int j), split(string s, string delimiter = " "), listFiles(string directory);
string replaceAll(string str, const string& from, const string& to), WSLPath(string path), toString(pair<double, double> xy), toString(vector<pair<double, double>> xys), toStringPrecise(pair<double, double> xy), toStringPrecise(vector<pair<double, double>> xys), toString(Picture pic);
void print(string), preComputeLonLatTab(), exitWithMessage(string s), loadMap(), loadBuildings(), write(unsigned int bestSimStrucId, pair<double, double> xy, unsigned short bestAngle, double z), printPicture(Picture pic), saveMap(), loadMapBinary(), freePicture(Picture pic); // could make a function "pause"
bool contains(string subject, string find), isIn(pair<double, double> xy, vector<pair<double, double>> XY), doesFileExist(string name);
int convertStrToInt(string str);
map<unsigned int, pair<double, double>> lonLatTab;
double convertStrToDouble(string str), getGroundAltitude(pair<double, double> xy), rd(double x);
vector<unsigned int> getNodesFromLine(unsigned int linesIndex);
pair<double, double> getLonLat(unsigned int nodeId), getCoordinates(pair<double, double> lonLat), barycenter(vector<pair<double, double>> XY);
vector<pair<double, double>> getPolygon(unsigned int linesIndex);
bool** tab(unsigned int x, unsigned int y);
pair<double, unsigned short> similarity(Picture pic0, Picture pic1);

bool WSL = true;
string path = WSLPath("C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\Candco\\CPP\\Projects\\LemnosLife\\Client\\Mess\\LemnosMap\\"); // how does this work ?
	   //pathToHeightFolder = WSLPath("C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\Candco\\CPP\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Lemnos\\Ground\\"),
string pathToHeightFolder = WSLPath("C:\\Users\\Benjamin\\Desktop\\map\\groundWSL\\"), // g++ compiler is bruh
	   NODE = "<nd ref=\"",
	   BEGIN_GRAVE_YARD = "<way ",
	   END_GRAVE_YARD = "</way>",
	   NODE_LOCATION = "<node id=\"",
	   LON_STR = " lon=\"",
	   LAT_STR = " lat=\"",
	   buildingsFolder = WSLPath("C:\\Users\\Benjamin\\Desktop\\map\\buildings\\blackOrWhiteWellSized\\"),
	   //buildingsSizedFolder = WSLPath(buildingsFolder + "sized\\"),
	   buildingsOSMFolder = WSLPath(buildingsFolder + "OSMWSL\\"),
	   mapBinFilePath = "map.bin",
	   pathObjectsFolder = WSLPath("C:\\Users\\Benjamin\\Desktop\\BensFolder\\DEV\\Candco\\CPP\\Projects\\LemnosLife\\Client\\Client\\ExecuteArea\\test\\CodeBlocks\\Extensions\\LemnosLife\\Map\\Lemnos\\Objects\\");

map<unsigned int, Picture> buildings;
vector<string> lines;
unsigned int linesSize, LINES_DEFAULT = UNSIGNED_INT_MAX;
double LON_MIN = 25.00,
	   LON_MAX = 25.50,
	   
	   LAT_MIN = 39.75,
	   LAT_MAX = 40.07,
	   
	   X_MAX = 42740.0,
	   Y_MAX = 35580.0,
	   
	   LON_FACT = X_MAX / (LON_MAX - LON_MIN),
	   LAT_FACT = Y_MAX / (LAT_MAX - LAT_MIN),

	   CHUNK_GROUND_SIZE = 1000.0,
	   SUB_CHK_SIZE = 100,
       SEA_BOTTOM = -100.0,
	   SUB_CHUNK_GROUND_SIZE = 10.0;
	   
map<string, vector<vector<vector<double>>>> mapChunkHeights;
char pathSeparator = '/';
vector<string> linesNodes;
unsigned int linesNodesSize, tooBigNb = 0, treated = 0;
double FACTOR = 100, MAX_SIZE = 256, GTX = 4600, GTY = 4770, preComputedFact = FACTOR * MAX_SIZE, preComputedFactX = preComputedFact / GTX, preComputedFactY = preComputedFact / GTY;
mutex workLock;
//atomic<unsigned int> threadsIndex = 0;
unsigned int threadsIndex = 0;

#define THREADING

void work(unsigned int linesIndex)
{
	//if(linesIndex < 296269)
	//	return;
	/*if(linesIndex < 295717)
		return;
	else if(linesIndex > 295717)
		exit(0);*/
	string line = lines[linesIndex];//linesNodes[linesIndex];
	{
        //if(contains(line, "k=\"building\" v=\"yes\"")) // isn't heavy
        {
            //print("Doing " + to_string(linesIndex) + " / " + to_string(/*linesNodesSize*/linesSize));
            // just to be as close as possible to python algorithm
			#ifndef THREADING
				print(to_string(linesIndex) + " " + to_string(linesSize) + " DOING");
			#endif
			vector<unsigned int> nodes = getNodesFromLine(linesIndex);
			unsigned int nodesSize = nodes.size();
            if(nodesSize == 0)
			{
				#ifndef THREADING
					print("ABORT: TOO BIG"); // just not a thing we want to consider
				//print("Abort this one !");
				#endif
				return;
			}
			vector<string> lineParts = split(line);
            unsigned int linePartsSize = lineParts.size();
            for(unsigned int linePartsIndex = 0; linePartsIndex < linePartsSize; linePartsIndex++)
            {
                string linePart = lineParts[linePartsIndex];
                nodes.push_back(convertStrToInt(linePart));
            }

            vector<pair<double, double>> lonLat, coo;
            for(unsigned int nodesIndex = 0; nodesIndex < nodesSize; nodesIndex++)
            {
                unsigned int node = nodes[nodesIndex];
				//print("node: " + to_string(node));
                pair<double, double> lonLatEl = getLonLat(node), coordinates = getCoordinates(lonLatEl);
                lonLat.push_back(lonLatEl);
                coo.push_back(coordinates);
                //print(to_string(coordinates.first) + "@" + to_string(coordinates.second));
            }
			//print("lonLat: " + toStringPrecise(lonLat));
            //return 0;

            double xMin = coo[0].first, xMax = coo[0].first, yMin = coo[0].second, yMax = coo[0].second;
            for(unsigned int nodesIndex = 0; nodesIndex < nodesSize; nodesIndex++)
            {
                pair<double, double> xy = coo[nodesIndex];
                double x = xy.first, y = xy.second;
                if(x < xMin)
                    xMin = x;
                if(x > xMax)
                    xMax = x;
                if(y < yMin)
                    yMin = y;
                if(y > yMax)
                    yMax = y;
            }

            double xD = xMax - xMin, yD = yMax - yMin;
            unsigned int xDelta = (int)(xD * preComputedFactX), yDelta = (int)(yD * preComputedFactY); // let's not care about rounding

            if(yDelta * xDelta >= 50000000)
            {
                //exitWithMessage("ABORT: TOO BIG");
				#ifndef THREADING
                	print("ABORT: TOO BIG");
				#endif
				tooBigNb += 1;
                return;//continue;
            }

            vector<pair<double, double>> XY = coo;// = polygons[linesIndex];// = getPolygon(linesIndex); // OMG - Nanni

            pair<double, double> xy = barycenter(XY);
			//print("XY: " + toStringPrecise(XY));
            //print(to_string(xy.first) + " " + to_string(xy.second));

            double z = getGroundAltitude(xy);
			//print("xy: " + toStringPrecise(xy) + " " + to_string(z));
            if(z <= 0)
            {
				#ifndef THREADING
                	print("ABORT: UNDER WATER");
				#endif			
				//underWaterNb += 1;
                return;//continue;
            }
            /*vector<vector<bool>>**/bool** pic = tab(xDelta, yDelta);

            double xDeltaD = xDelta, yDeltaD = yDelta;
            for(unsigned int yT = 0; yT < yDelta; yT++)
            {
                for(unsigned int xT = 0; xT < xDelta; xT++)
                {
                    pair<double, double> xyT = make_pair(xMin + (xT / xDeltaD) * xD, yMin + (yT / yDeltaD) * yD);
                    //pair<double, double> xyT = make_pair(xMin + 0.5 * xD, yMin + 0.5 * yD); // oups someone forgot this :')
                    //print(toString(xyT));
                    //print(toString(XY));
                    if(isIn(xyT, XY))
					{
                        //print("hey !");
                        pic[yT][xT] = CST_T;
                        //return 0;
                    }
                }
            }
			//print("XY: " + toStringPrecise(XY));
            double bestSim = 0;
            unsigned int bestSimStrucId = 0;
            unsigned short bestAngle = 0;
            Picture picture = {pic, yDelta, xDelta};

			//unsigned int debugIndex = 0;
            //print("bef"); // main time spent in the following for loop
            for(map<unsigned int, Picture>::iterator it = buildings.begin(); it != buildings.end(); it++)
            {
                unsigned int strucId = it->first;
                Picture building = buildings[strucId];
                /*print("BUILDING START " + to_string(strucId));
                printPicture(building);
                print("BUILDING STOP");*/
                /*print("PICTURE START");
                printPicture(picture); /// TODO: warning got mirror on Python
                print("PICTURE STOP");*/
				//exit(0);
                pair<double, unsigned short> simAngle = similarity(building, picture);
                double sim = simAngle.first;
                unsigned short angle = simAngle.second;
                //print(to_string(strucId) + " " + /*to_string*/convertNbToStr(sim) + " " + to_string(angle));
				//if(strucId == 417)
				//	exit(0);
				if(sim > bestSim)
                {
                    bestSim = sim;
                    bestSimStrucId = strucId;
                    bestAngle = (angle + 90) % 360;
                }
            }
            // could store in strucs, sims and angle
			#ifdef THREADING
				workLock.lock();
				threadsIndex++; // doesn't need to be atomic so
				print("Done " + to_string(threadsIndex) + " / " + to_string(/*linesNodesSize*/linesSize));
			#endif
			//print(convertNbToStr(bestSimStrucId) + " " + convertNbToStr(rd(xy.first)) + " " + convertNbToStr(rd(xy.second)) + " " + convertNbToStr(bestAngle) + " " + convertNbToStr(rd(z)));
			print(to_string(bestSimStrucId) + " " + to_string_with_precision(rd(xy.first), 2) + " " + to_string_with_precision(rd(xy.second), 2) + " " + to_string(bestAngle) + " " + to_string_with_precision(rd(z), 2));
			//if(bestSimStrucId == 417)
			//	exit(0);
			//if(bestSimStrucId == 0)
			//	exit(0);
			//print(to_string(bestSimStrucId) + " |" + toString(xy) + "| " + to_string(bestAngle) + " " + to_string(z));
            if(bestSimStrucId != 0)
				write(bestSimStrucId, xy, bestAngle, z);
			#ifdef THREADING
				workLock.unlock();
			#endif

            //free(pic);
            freePicture(picture);
			//exit(0);
            //treated++;
            //if(treated == 8)
                ;//break;
        }
	} // indenting is boring/complicated on vim
}

int main()
{
	//exitWithMessage(path);
	string OSMFile = "OSM.xml";//"OSMCleanWSL.xml";

	print("loading " + OSMFile);

	chdir(path.c_str());
	
	lines = getFileContent(OSMFile);
	linesSize = lines.size();
	//print("linesSize: " + to_string(linesSize));

	print("loading lon lat table");

	preComputeLonLatTab();

	print("loading map");

	//loadMapBinary(); // single-threaded binary version only saves 1 tenth of time (about 3s) - maybe multithreading would make it faster ?
	loadMap();
	//print("map loaded !");
	//saveMap(); // around 30 s for one or all files (multi-threading could also help but this operation is supposed to be executed only once)

	print("loading buildings");

	loadBuildings();

	print("going to work !");
	//return 0;

	/*vector<vector<pair<double, double>>> polygons;
	vector<string> lines = getFileContent("polygon.txt");
	unsigned int linesSize = lines.size();
	for(unsigned int linesIndex = 0; linesIndex < linesSize; linesIndex++)
	{
		string line = lines[linesIndex];
		vector<string> lineParts = split(line);
		vector<pair<double, double>> vec;
		unsigned int linePartsSize = lineParts.size();
		for(unsigned int linePartsIndex = 0; linePartsIndex < linePartsSize; linePartsIndex++)
		{
			string linePart = lineParts[linePartsIndex];
			vector<string> linePartParts = split(linePart, ",");
			pair<double, double> p = {convertStrToDouble(linePartParts[0]), convertStrToDouble(linePartParts[1])};
			vec.push_back(p);
		}
		polygons.push_back(vec);
	}*/

	//linesNodes = getFileContent("nodesIds.txt");
	//linesNodesSize = linesNodes.size();
	//thread threads[/*linesNodesSize*/linesSize];
	vector<thread> threads; // maybe limiting threads number could make it faster
	for(unsigned int linesIndex = 0; linesIndex < linesSize/*linesNodesSize*/; linesIndex++)
	{
		//work(linesIndex);
		string line = lines[linesIndex];
        if(contains(line, "k=\"building\" v=\"yes\""))
		{
			#ifdef THREADING
				threads.push_back(thread(work, linesIndex));
			#else
				work(linesIndex);
			#endif
		}
		//threads[linesIndex] = thread(work, linesIndex);
	}
	#ifdef THREADING
		unsigned int threadsSize = threads.size();
		for(unsigned int linesIndex = 0; linesIndex < /*linesNodesSize*/threadsSize; linesIndex++)
		{
			threads[linesIndex].join();
		}
	#endif
	print("Freeing...");

	// I don't know whether or not the system does it but here it is
	for(map<unsigned int, Picture>::iterator it = buildings.begin(); it != buildings.end(); it++)
	{
		//print("Freeing " + to_string(it->first));
		//free(it->second.pic); // freeing just a single pointer doesn't pay the bill :')
		freePicture(it->second);
	}

	print("FINISHED ALL !");

	//print("hey");
	return 0;
}

string toString(Picture pic) // not going to display all bits noobs
{
	return to_string(pic.h) + " " + to_string(pic.w);
}

bool doesFileExist(string name)
{
    struct stat buffer;
    return stat(name.c_str(), &buffer) == 0;
}

void freePicture(Picture pic)
{
	for(unsigned int i = 0; i < pic.h; i++)
        free(pic.pic[i]);
	free(pic.pic);
}

string toString(pair<double, double> xy)
{
	return convertNbToStr(xy.first) + " " + convertNbToStr(xy.second);
}

string toString(vector<pair<double, double>> xys)
{
	unsigned int xysSize = xys.size();
	string res = "";
	for(unsigned int xysIndex = 0; xysIndex < xysSize; xysIndex++)
	{
		pair<double, double> xy = xys[xysIndex];
		res += toString(xy);
		if(xysIndex < xysSize - 1)
			res += "\n";
	}
	return res;
}

string toStringPrecise(pair<double, double> xy)
{
    return to_string(xy.first) + " " + to_string(xy.second);
}

string toStringPrecise(vector<pair<double, double>> xys)
{
    unsigned int xysSize = xys.size();
    string res = "";
    for(unsigned int xysIndex = 0; xysIndex < xysSize; xysIndex++)
    {
        pair<double, double> xy = xys[xysIndex];
        res += toStringPrecise(xy);
        if(xysIndex < xysSize - 1)
            res += "\n";
    }
    return res;
}

void saveMap()
{
	print("Saving map...");
	/*ofstream mapBinFile(mapBinFilePath, fstream::binary);
    cereal::BinaryOutputArchive oarchive(mapBinFile);
    oarchive(mapChunkHeights);
    mapBinFile.close();*/

	for(map<string, vector<vector<vector<double>>>>::iterator it = mapChunkHeights.begin(); it != mapChunkHeights.end(); it++)
	{
		string chunkName = it->first, path = "map/" + chunkName + ".bin";
		//vector<vector<vector<double>>
		ofstream mapBinFile(path, fstream::binary);
   		cereal::BinaryOutputArchive oarchive(mapBinFile);
    	oarchive(it->second);
    	mapBinFile.close();
	}

	print("Map saved !");
}

//atomic<unsigned int> threads;
mutex mapChunkHeightsLock;

void loadMapChunkBinary(string file)
{
	string key = replaceAll(replaceAll(file, ".bin", ""), "/", "");
	ifstream mapBinFile("map" + file, ifstream::binary);
    cereal::BinaryInputArchive iarchive(mapBinFile);
    vector<vector<vector<double>>> tmp;
	//mapChunkHeightsLock.lock();
	iarchive(/*mapChunkHeights[key]*/tmp);
	//mapChunkHeightsLock.unlock();
    mapBinFile.close();
	mapChunkHeightsLock.lock(); // the first try without mutex was a success... but no more ^^
	mapChunkHeights[key] = tmp;
	mapChunkHeightsLock.unlock();
	//threads--;
}

void loadMapBinary()
{
	//print("Loading map...");
	/*ifstream mapBinFile(mapBinFilePath, ifstream::binary);
    cereal::BinaryInputArchive iarchive(mapBinFile);
    iarchive(mapChunkHeights);
    mapBinFile.close();
	return;*/
	
	vector<string> files = listFiles("map");
	unsigned int filesSize = files.size();
	//threads = filesSize;
	thread ths[/*threads*/filesSize];
	for(unsigned int filesIndex = 0; filesIndex < filesSize; filesIndex++) // 26 s in mono thread
	{
		string file = files[filesIndex];/*, key = replaceAll(replaceAll(file, ".bin", ""), "/", ""), path = "map" + file;
		//print("!" + path + "!");
		ifstream mapBinFile(path, ifstream::binary);
    	cereal::BinaryInputArchive iarchive(mapBinFile);
		vector<vector<vector<double>>> tmp;
    	iarchive(/*mapChunkHeights[key]*//*tmp);
		//print("!" + key + "!");
		mapChunkHeights[key] = tmp;
    	mapBinFile.close();*/
		ths[filesIndex] = thread(loadMapChunkBinary, file); // could reduce number of concurrent threads but now we divided time wait by 3 it's ok
		//thread th(loadMapChunkBinary, file);
        //th.detach();
		//th.join();
	}
	for(unsigned int filesIndex = 0; filesIndex < filesSize; filesIndex++) // 26 s in mono thread
    {
		ths[filesIndex].join();
	}
	/*while(threads > 0)
	{
		print("Waiting" + to_string(threads) + " threads...");
		sleep(1);
	}*/

	//print("Map loaded !");
}

double remainderEuclidianDivision(double dividend, double divisor)
{
    return fmod(dividend, divisor);
}

double roundUnit(double x) // likewise respect Python convention
{
	/// RESTORE THIS TO HAVE SAME RESULTS AS PYTHON ! (without it the algorithm seems very faster (x8 in fact))
	/*if(remainderEuclidianDivision(x, 1) == 0.5)
	{
		//print("it happened");
		//exit(0);
		return x - 0.5; // used to be 0 here and if(x == 0.5) :')
	}*/
	return round(x);
}

double rd(double x)
{
	return roundUnit(x * 100.0) / 100.0;
}

string strInt(int x)
{
	return convertNbToStr(rd(x)); // to_string has too many decimals
}

bool writeFile(string filePath, string option, string toWrite)
{
    FILE* file = fopen(filePath.c_str(), option.c_str());
    if(file != NULL)
    {
        fputs(toWrite.c_str(), file);
        fclose(file);
        return true;
    }
    return false;
}

void write(unsigned int bestSimStrucId, pair<double, double> xy, unsigned short bestAngle, double z)
{
	double x = xy.first, y = xy.second;
	int chkX = (int)(x / CHUNK_GROUND_SIZE), chkY = (int)(y / CHUNK_GROUND_SIZE);
	string file = pathObjectsFolder + strInt(chkX) + " " + strInt(chkY) + ".objects";
	double subChkX = ((int)(x / SUB_CHK_SIZE)) % ((int)SUB_CHUNK_GROUND_SIZE), subChkY = ((int)(y / SUB_CHK_SIZE)) % ((int)SUB_CHUNK_GROUND_SIZE);
	string subChkHeader = strInt(subChkX) + " " + strInt(subChkY),
		   line = to_string(bestSimStrucId) + " " + convertNbToStr(rd(remainderEuclidianDivision(x, SUB_CHK_SIZE))) + " " + convertNbToStr(rd(remainderEuclidianDivision(y, SUB_CHK_SIZE))) + " " + convertNbToStr(rd(z)) + " " + to_string((int)bestAngle);
	vector<string> fLines;
	if(doesFileExist(file))
	{
		fLines = getFileContent(file);
	}
	unsigned int fLinesSize = fLines.size(), subChkHeaderIndex;
	bool subChkHeaderPresent = false;
	for(unsigned int fLinesIndex = 0; fLinesIndex < fLinesSize; fLinesIndex++)
	{
		string fLine = fLines[fLinesIndex];
		if(fLine == subChkHeader)
		{
			subChkHeaderPresent = true;
			subChkHeaderIndex = fLinesIndex;
			break;
		}
	}
	string toWrite = "";
	if(subChkHeaderPresent)
	{
		for(unsigned int fLinesIndex = 0; fLinesIndex < fLinesSize; fLinesIndex++)
		{
			string fLine = fLines[fLinesIndex];
			if(fLinesIndex < fLinesSize - 1)
				fLine += "\n";
			toWrite += fLine;
			if(fLinesIndex == subChkHeaderIndex)
				toWrite += line + "\n";
		}
	}
	else
	{
		for(unsigned int fLinesIndex = 0; fLinesIndex < fLinesSize; fLinesIndex++)
        {
            string fLine = fLines[fLinesIndex];
			if(fLinesIndex < fLinesSize - 1)
				fLine += "\n";
			toWrite += fLine;
		}
		if(fLinesSize != 0)
		{
			toWrite += "\n";
		}
		toWrite += subChkHeader + "\n";
		toWrite += line;
	}
	writeFile(file, "w", toWrite);
}

double toRad(unsigned short angle)
{
	return angle * (PI / 180);
}

pair<double, double> rotate(pair<double, double> point, double angle)
{
	double px = point.first, py = point.second;
	//#define qx cos(angle) * px - sin(angle) * py
	//#define qy sin(angle) * px + cos(angle) * py
	// don't used anymore because macro make compiler goes crazy
	double qx = cos(angle) * px - sin(angle) * py, qy = sin(angle) * px + cos(angle) * py;
	return {qx, qy};
}

pair<unsigned int, unsigned int> rotates(double x, double y, double angle)
{
	bool first = true;
	double angleRad = toRad(angle); // oups someone forgot this #BlackMirror
	double xMin, xMax, yMin, yMax;
	vector<pair<double, double>> points = {{x, 0}, {x, y}, {0, 0}, {0, y}};
	for(unsigned short i = 0; i < 4; i++)
	{
		pair<double, double> point = rotate(points[i], angleRad);
		double x = point.first, y = point.second;
		if(first || x > xMax)
			xMax = x;
	    if(first || x < xMin)
			xMin = x;
		if(first || y > yMax)
            yMax = y;
        if(first || y < yMin)
            yMin = y;
		first = false;
	}
	return {ceil(xMax - xMin), ceil(yMax - yMin)};
}

Picture tabPicture(unsigned int x, unsigned int y)
{
	bool** pic = tab(x, y);
	/*Picture pic;
	pic.pic = tab(x, y);
	pic.w = x;
	pic.h = y;*/
	return {pic, y, x};
}

#define DDD 424242

void printPicture(Picture pic)
{
	for(unsigned int y = 0; y < pic.h; y++)
	{
		for(unsigned int x = 0; x < pic.w; x++)
		{
			cout << (pic.pic[y][x] == CST_T ? CST_T_STR : CST_F_STR);
		}
		cout << endl;
	}
}

Picture extract(Picture pic)
{
	//print("STOP A");
	//printPicture(pic);
	//print("STOP B");
	unsigned int y = pic.h, x = pic.w, xMin = DDD, xMax = DDD, yMin = DDD, yMax = DDD, yI = 0, xI;
	bool notBreak = true;
	while(yI < y && notBreak)
	{
		xI = 0;
		while(xI < x && notBreak)
		{
			if(pic.pic[yI][xI] == CST_T)
			{
				yMin = yI;
				notBreak = false;
			}
			xI++;
		}
		yI++;
	}
	xI = 0;
	notBreak = true;
	while(xI < x && notBreak)
    {
        yI = 0;
        while(yI < y && notBreak)
        {
            if(pic.pic[yI][xI] == CST_T)
            {
                xMin = xI;
                notBreak = false;
            }
            yI++;
        }
        xI++;
    }
	yI = y - 1;
	notBreak = true;
	while(yI >= 0 && notBreak)
	{
		xI = 0;
		while(xI < x && notBreak)
		{
			if(pic.pic[yI][xI] == CST_T)
			{
				yMax = yI;
				notBreak = false;
			}
			xI += 1;
		}
		yI -= 1;
	}
	xI = x - 1;
	notBreak = true;
	while(xI >= 0 && notBreak)
	{
		yI = 0;
		while(yI < y && notBreak)
		{
			if(pic.pic[yI][xI] == CST_T)
			{
				xMax = xI;
				notBreak = false;
			}
			yI++;
		}
		xI--;
	}
	Picture extracted = tabPicture(xMax - xMin + 1, yMax - yMin + 1);
	for(unsigned int yI = yMin; yI < yMax + 1; yI++)
	{
		for(unsigned int xI = xMin; xI < xMax + 1; xI++)
		{
			extracted.pic[yI - yMin][xI - xMin] = pic.pic[yI][xI];
		}
	}
	//print("EXTRACTED A");
	//printPicture(extracted);
	//print("EXTRACTED B");
	return extracted;
}

//unsigned int dbgIndex = 0;

Picture redim(Picture pic, unsigned int x, unsigned int y)
{
	unsigned int picY = pic.h, picX = pic.w;
	Picture res = tabPicture(x, y);
	//print("pic start");
	//printPicture(pic);
	//print("pic stop");
	double factFX = ((double)(picX - 1)) / (x - 1), factFY = ((double)(picY - 1)) / (y - 1);
	//print("x, y: " + to_string(x) + " " + to_string(y));
	//print("picX, picY: " + to_string(picX) + " " + to_string(picY));
	//print("factFX, factFY: " + convertNbToStr(factFX) + " " + convertNbToStr(factFY));
	//print("factFX, factFY: " + to_string(factFX) + " " + to_string(factFY));
	// same parameters but for loop seems to give bit different results... (in comparaison with Python script)
	for(unsigned int yT = 0; yT < y; yT++)
	{
		for(unsigned int xT = 0; xT < x; xT++)
		{
			unsigned int xI = roundUnit(xT * factFX), yI = roundUnit(yT * factFY); // 0.5 be like quantum physics round(2.5) and round(3.5) on Python are quite funny
			//if(xT == x - 1/* && dbgIndex == 360*/)
			/*{
				print("dbgIndex: " + to_string(dbgIndex));
				print("xI, yI: " + to_string(xI) + " " + to_string(yI));
				print("xT, factFX: " + to_string(xT) + " " + to_string(factFX));
				print("yT, factFY: " + to_string(yT) + " " + to_string(factFY));
			}*/
			res.pic[yT][xT] = pic.pic[yI][xI];
		}
		//break;
	}
	//free(pic.pic);
	freePicture(pic);
	//printPicture(res);
	//exit(0);
	//dbgIndex++;
	return res;
}

double DBG = 2;

Picture rotatePic(Picture pic, unsigned short angle)
{
	//print("pic: " + toString(pic));
	double angleRad = toRad(angle);
	unsigned int y = pic.h, x = pic.w;
	double d = sqrt(y * y + x * x);
	pair<unsigned int, unsigned int> rot = rotates(x, y, angle);
	unsigned int sX = rot.first, sY = rot.second, xC = x / 2, yC = y / 2;
	double factX = ((double)(x - 1)) / (sX - 1), factY = ((double)(y - 1)) / (sY - 1);
	/*print("pic start");
	printPicture(pic);
	print("pic stop");*/
	Picture rotatedBig = tabPicture(sX, sY);
	for(unsigned int yT = 0; yT < sY; yT++)
	{
		for(unsigned int xT = 0; xT < sX; xT++)
		{
			double xI = ((double)(xT)) * factX, yI = ((double)yT) * factY; // used to be int
			xI -= xC;
			yI -= yC;
			xI *= DBG;
			yI *= DBG;
			pair<double, double> point = {xI, yI};
			point = rotate(point, angleRad);
			point.first += xC;
			point.second += yC;
			unsigned int xF = roundUnit(point.first), yF = roundUnit(point.second); // does it round well ? - well I don't know even if with round it is ok 
			if(yF < y && yF >= 0 && xF < x && xF >= 0)
				rotatedBig.pic[yT][xT] = pic.pic[yF][xF];
		}
	}
	/*print("rotatedBig start");
	printPicture(rotatedBig);
	print("rotatedBig stop");
	print("rotatedBig: " + toString(rotatedBig));*/
	Picture rotated = extract(rotatedBig);
	//free(rotatedBig.pic);
	/*print("rotated start");
	printPicture(rotated);
	print("rotated stop");*/
	freePicture(rotatedBig);
	//exit(0);
	//print("rotated: " + toString(rotated));
	Picture res = redim(rotated, sX, sY);
	/*print("res start");
    printPicture(res);
    print("res stop");*/
	//print("res: " + toString(res));
	return res;
}

double similarityOneToOther(Picture pic0, Picture pic1)
{
	unsigned int pic0Y = pic0.h, pic0X = pic0.w, pic1Y = pic1.h, pic1X = pic1.w;
	//print("pic0Y, pic0X: " + to_string(pic0Y) + " " + to_string(pic0X));
	//print("pic1Y, pic1X: " + to_string(pic1Y) + " " + to_string(pic1X));
	if(pic0Y > pic1Y or pic0X > pic1X)
	{
		//print("too small guys !");
		return 0;
	}
	unsigned int yMax = min(pic0Y, pic1Y), xMax = min(pic0X, pic1X), s = 0, total = max(pic0Y, pic1Y) * max(pic0X, pic1X); // min and max are already known here...
	
	/*print("pic0 start");
	printPicture(pic0);
	print("pic0 stop");*/

	/*print("pic1 start");
    printPicture(pic1);
    print("pic1 stop");*/

	/*print("yMax, xMax: " + convertNbToStr(yMax) + " " + convertNbToStr(xMax));*/
	for(unsigned int y = 0; y < yMax; y++)
	{
		for(unsigned int x = 0; x < xMax; x++)
		{
			if(pic0.pic[y][x] == pic1.pic[y][x])
				s += 1;
		}
	}
	//print("res: " + convertNbToStr(s) + " " + convertNbToStr(total));
	double res = 100.0 * ((double)(s)) / total; // may have problem because some are integers here
	return res;
}

pair<double, unsigned short> similarity(Picture pic0, Picture pic1) // used to be bool** but we don't have size info likewise
{
	double sim0 = 0;
	unsigned short bestAngle = 0;
	/*print("pic0 start");
	printPicture(pic0);
	print("pic0 stop");
	print("pic1 start");
	printPicture(pic1);
	print("pic1 stop");
	exit(0);*/
	for(unsigned short angle = 0; angle < 360; angle++)
	{
		//print("angle: " + to_string(angle));
		Picture pic0Tmp = rotatePic(pic0, angle);
		/*print("pic0Tmp start");
		printPicture(pic0Tmp);
		print("pic0Tmp stop");
		print("pic1 start");
		printPicture(pic1);
		print("pic1 stop");*/
		// sometimes suddenly to big so involves 0 similitude
		double sim0Tmp = similarityOneToOther(pic0Tmp, pic1);
		//print("sim: " + to_string(angle) + " " + /*to_string*//*convertNbToStr*/to_string(sim0Tmp));
		//if(sim0Tmp > 0)
		//	exit(0);
		//break;
		if(sim0Tmp > sim0)
		{
			sim0 = sim0Tmp;
			bestAngle = angle;
		}
		//free(pic0Tmp.pic);
		freePicture(pic0Tmp);
	}
	//if(sim0 > 0)
	//	exit(0);
	return make_pair(sim0, bestAngle); // no sim1 for the moment
}

// we could serialize map and buildings to make init faster but for the moment it is very gadget
void loadBuildings()
{
	vector<string> files = listFiles(buildingsOSMFolder); // assume Python script run first once for preparing stuff - listFiles seems to return fileName with a slash previous to it :(
	unsigned int filesSize = files.size();
	for(unsigned int filesIndex = 0; filesIndex < filesSize; filesIndex++)
	{
		string file = replaceAll(files[filesIndex], "/", ""), fileName = split(file, ".")[0], path = buildingsOSMFolder + file;
		vector<string> lines = getFileContent(buildingsOSMFolder + file);
		//print("!" + lines[0] + "!");
		unsigned int linesSize = lines.size(), lineSize = lines[0].length(), strucId = convertStrToInt(fileName);
		bool** pic = tab(lineSize, linesSize);
		for(unsigned int y = 0; y < linesSize; y++)
		{
			for(unsigned int x = 0; x < lineSize; x++)
			{
				if(lines[y][x] == CST_T_STR)
					pic[y][x] = CST_T;
			}
		}
		Picture picture = {pic, linesSize, lineSize};//{.pic = pic, .w = lineSize, .h = linesSize};
		//print("strucId: " + to_string(strucId) + " (" + fileName + " - " + path + ")");
		buildings[strucId] = picture;
	}
}

// https://stackoverflow.com/a/15599478
bool isIn(pair<double, double> xy, vector<pair<double, double>> XY)
{
    int XYSize = XY.size();
    bool c = false;

	double x = xy.first, y = xy.second;
    for(int i = 0, j = XYSize - 1; i < XYSize; j = i++)
	{
		pair<double, double>* pi = &XY[i], *pj = &XY[j];
		double ix = pi->first, iy = pi->second, jx = pj->first, jy = pj->second;
        if(((iy >= y) != (jy >= y)) && (x <= (jx - ix) * (y - iy) / (jy - iy) + ix))
            c = !c;
    }
    return c;
}

double determinant(pair<double, double> ab, pair<double, double> axy)
{
    return ab.first * axy.second - ab.second * axy.first;
}

double determinant(pair<double, double> a, pair<double, double> b, pair<double, double> xy)
{
	pair<double, double> ab = make_pair(b.first - a.first, b.second - a.second), axy = make_pair(xy.first - a.first, xy.second - a.second);
    return determinant(ab, axy);
}

bool pointIsOnLeft(pair<double, double> xy, pair<double, double> a, pair<double, double> b)
{
    return determinant(a, b, xy) <= 0;
}

bool isInOneSide(pair<double, double> xy, vector<pair<double, double>> XY)
{
	unsigned int XYSize = XY.size();
    for(unsigned short XYIndex = 0; XYIndex < XYSize - 1; XYIndex++)
    {
        bool isLeft = pointIsOnLeft(xy, XY[XYIndex], XY[XYIndex + 1]);
        if(!isLeft)
            return false;
    }
    bool res = pointIsOnLeft(xy, XY[XYSize - 1], XY[0]);
	return res;
}

// mine doesn't work fine with concave things in comparaison with stackoverflow answer
/*bool isIn(pair<double, double> xy, vector<pair<double, double>> XY)
{
	//print("Before: " + to_string(XY.size()));
	XY.pop_back();
	//print("After: " + to_string(XY.size()));
	bool firstSide = isInOneSide(xy, XY);
	reverse(XY.begin(), XY.end());
	return firstSide || isInOneSide(xy, XY);
}*/

/*vector<vector<bool>>**/bool** tab(unsigned int x, unsigned int y)
{
	/*vector<bool> v;
	for(unsigned short i = 0; i < x; i++)
		v.push_back(CST_F); // or could use a C++ constructor of vector ?
	vector<vector<bool>>* res = new vector<vector<bool>>(y);*/
	bool** res = (bool**)malloc(y * sizeof(bool*));
	for(unsigned int i = 0; i < y; i++)
		res[i] = (bool*)malloc(x * sizeof(bool));
	for(unsigned int yT = 0; yT < y; yT++) // not like python there seems to be some '1'
    	for(unsigned int xT = 0; xT < x; xT++)
        	res[yT][xT] = CST_F;
	return res;
}

bool startsWith(string subject, string test)
{
    return !subject.compare(0, test.size(), test);
}

void listFiles(string direc, vector<string> *str)
{
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(direc.c_str())) != NULL)
    {
        while((ent = readdir(dir)) != NULL)
        {
            string file = ent->d_name;
            if(!startsWith(file, "."))
            {
                string path = ""; // used to be direc
                if(path[path.length() - 1] != pathSeparator)
                    path += pathSeparator;
                path += file;
                if(file.find_last_of(".") > file.length())
                    listFiles(path, str);
                else
                    str->push_back(path);
            }
        }
        closedir(dir);
    }
}

vector<string> listFiles(string directory)
{
	vector<string> files;
	listFiles(directory, &files);
	return files;
}

void loadMap()
{
	vector<string> files = listFiles(pathToHeightFolder);
	unsigned int filesSize = files.size();
	for(unsigned int filesIndex = 0; filesIndex < filesSize; filesIndex++)
	{
		//print(to_string(filesIndex) + " / " + to_string(filesSize));
		string file = replaceAll(files[filesIndex], "/", ""), chunkName = split(file, ".")[0];
		vector<string> chunkNameParts = split(chunkName, " ");
		int chkXThousand = convertStrToInt(chunkNameParts[0]) * CHUNK_GROUND_SIZE,
		    chkYThousand = convertStrToInt(chunkNameParts[1]) * CHUNK_GROUND_SIZE;
		vector<string> lines = getFileContent(pathToHeightFolder + file);
		unsigned int linesSize = lines.size() - 1;
	
		vector<vector<vector<double>>> lineChunksHeights;
		for(unsigned short lineIndex = 0; lineIndex < linesSize; lineIndex++)
		{
			vector<string> partsCurrentLine = split(lines[lineIndex]);

			unsigned int partsCurrentLineSize = partsCurrentLine.size() - 1;
			vector<vector<double>> columnChunksHeights;
			for(unsigned int columnIndex = 0; columnIndex < partsCurrentLineSize; columnIndex++)
			{
				unsigned short chkYThousandPlusChunkGroundSize = chkYThousand + CHUNK_GROUND_SIZE,
							   xMin = chkXThousand + columnIndex * SUB_CHUNK_GROUND_SIZE,
							   yMin = chkYThousandPlusChunkGroundSize - lineIndex * SUB_CHUNK_GROUND_SIZE;							   

				double vertex[3] = {xMin, yMin, convertStrToDouble(partsCurrentLine[columnIndex])};

				vector<double> vertexVector;
				for(unsigned short i = 0; i < 3; i++)
					vertexVector.push_back(vertex[i]);
				columnChunksHeights.push_back(vertexVector);
			}
			lineChunksHeights.push_back(columnChunksHeights);
		}
		//print("loading chk: " + chunkName + "!");
		mapChunkHeights[chunkName] = lineChunksHeights;
	}
}

double groundAltitudeTopLeft(Vector3D A, Vector3D AB, Vector3D AD, Vector3D P)
{
    double abZ = AB.Z * ((SUB_CHUNK_GROUND_SIZE - P.X) / SUB_CHUNK_GROUND_SIZE), adZ = AD.Z * ((SUB_CHUNK_GROUND_SIZE - P.Y) / SUB_CHUNK_GROUND_SIZE); // used to be 4
    return A.Z + abZ + adZ;
}

double groundAltitudeTopRight(Vector3D B, Vector3D DC, Vector3D BC, Vector3D P)
{
    double dcZ = DC.Z * ((P.X) / SUB_CHUNK_GROUND_SIZE), bcZ = BC.Z * ((P.Y) / SUB_CHUNK_GROUND_SIZE);
    return B.Z + dcZ + bcZ;
}

bool pointIsInTriangle(Vector2D P, Vector2D A, Vector2D B, Vector2D C)
{
    return determinant(A, B, P) <= 0 && determinant(B, C, P) <= 0 && determinant(C, A, P) <= 0;
}

bool pointIsInTriangle(Vector3D P, Vector3D A, Vector3D B, Vector3D C)
{
    return pointIsInTriangle(Vector2D(P), Vector2D(A), Vector2D(B), Vector2D(C));
}

double groundAltitudePoints(Vector3D A, Vector3D B, Vector3D C, Vector3D D, Vector3D P)
{
    Vector3D AN = Vector3D(0, SUB_CHUNK_GROUND_SIZE, A.Z), BN = Vector3D(SUB_CHUNK_GROUND_SIZE, SUB_CHUNK_GROUND_SIZE, B.Z),
             CN = Vector3D(SUB_CHUNK_GROUND_SIZE, 0, C.Z), DN = Vector3D(0, 0, D.Z), PN = moduloVector(P, SUB_CHUNK_GROUND_SIZE);
    return pointIsInTriangle(PN, AN, BN, CN) ? groundAltitudeTopLeft(BN, Vector3D(BN, AN), Vector3D(BN, DN), PN) : groundAltitudeTopRight(CN, Vector3D(CN, DN), Vector3D(CN, AN), PN);
}

long long timeIn(double dividend, double divisor)
{
    return (dividend - remainderEuclidianDivision(dividend, divisor)) / divisor;
}

int indexInMatrix(double coordinate)
{
    return timeIn(remainderEuclidianDivision(coordinate, CHUNK_GROUND_SIZE), SUB_CHUNK_GROUND_SIZE);
}

string getChunk1kName(double coordinates[2])
{
    unsigned short coo[2];
    for(unsigned short i = 0; i < 2; i++)
    {
        coo[i] = floor(coordinates[i]);
        coo[i] = (coo[i] - remainderEuclidianDivision(coo[i], CHUNK_GROUND_SIZE)) / CHUNK_GROUND_SIZE;
    }
    return to_string(coo[0]) + " " + to_string(coo[1]);
}

double getGroundAltitude(pair<double, double> xy)
{
	double x = xy.first, y = xy.second, coordinates[2] = {x, y}, coordinatesRight[2] = {x + CHUNK_GROUND_SIZE, y}, coordinatesTop[2] = {x, y - CHUNK_GROUND_SIZE}, coordinatesTopRight[2] = {x + CHUNK_GROUND_SIZE, y - CHUNK_GROUND_SIZE};

    string chkName = getChunk1kName(coordinates), chkNameRight = getChunk1kName(coordinatesRight), chkNameTop = getChunk1kName(coordinatesTop), chkNameTopRight = getChunk1kName(coordinatesTopRight);

	//print("A " + chkName + "!");

    if(mapChunkHeights.find(chkName) == mapChunkHeights.end()) return SEA_BOTTOM;

    vector<vector<vector<double>>> *matrix = &mapChunkHeights[chkName], *matrixTop, *matrixRight, *matrixTopRight;

    int indexX = indexInMatrix(x), indexY = indexInMatrix(y) + 1,
        matrixSize = CHUNK_GROUND_SIZE / SUB_CHUNK_GROUND_SIZE;

	//print("B");

    if(matrix->size() <= matrixSize - indexY) return 0;
    vector<double> vec = matrix->at(matrixSize - indexY)[indexX];
    Vector3D A = Vector3D(vec), B, C, D;

    if(indexX + 1 >= matrixSize)
    {
        if(mapChunkHeights.find(chkNameRight) == mapChunkHeights.end()) return SEA_BOTTOM;
        matrixRight = &mapChunkHeights[chkNameRight];
        B = Vector3D(matrixRight->at(matrixSize - indexY)[0]);
    }
    else
        B = Vector3D(matrix->at(matrixSize - indexY)[indexX + 1]);

	//print("C");

    if(indexY == 1)
    {
        if(mapChunkHeights.find(chkNameTop) == mapChunkHeights.end()) return SEA_BOTTOM;
        matrixTop = &mapChunkHeights[chkNameTop];
        C = Vector3D(matrixTop->at(0)[indexX]);
    }
    else
        C = Vector3D(matrix->at(matrixSize - indexY + 1)[indexX]);

	//print("D");

    if(indexX + 1 >= matrixSize)
    {
        if(indexY == 1)
        {
            if(mapChunkHeights.find(chkNameTopRight) == mapChunkHeights.end()) return SEA_BOTTOM;
            matrixTopRight = &mapChunkHeights[chkNameTopRight];
            D = Vector3D(matrixTopRight->at(0)[0]);
        }
        else
            D = Vector3D(matrixRight->at(matrixSize - indexY + 1)[0]);
    }
    else
        D = indexY == 1 ? Vector3D(matrixTop->at(0)[indexX + 1]) : Vector3D(matrix->at(matrixSize - indexY + 1)[indexX + 1]);

    Vector3D P = Vector3D(x, y, 0);

	//print(toString(A) + "|" + toString(B) + "|" + toString(C) + "|" + toString(D) + "|" + toString(P));
    double groundAltitude = groundAltitudePoints(A, B, C, D, P);
    return groundAltitude;
}

pair<double, double> barycenter(vector<pair<double, double>> XY)
{
	unsigned int XYSize = XY.size();
	pair<double, double> xy = make_pair(0, 0);
	for(unsigned int XYIndex = 0; XYIndex < XYSize; XYIndex++)
	{
		pair<double, double> xyTmp = XY[XYIndex];
		xy.first += xyTmp.first; // can we add two pair<double, double> ?
		xy.second += xyTmp.second;
	}
	xy.first /= XYSize;
	xy.second /= XYSize;
	return xy;
}

pair<double, double> getCoordinatesFromNodeId(unsigned int node)
{
	return getCoordinates(getLonLat(node));
}

vector<pair<double, double>> getPolygon(unsigned int linesIndex)
{
	vector<unsigned int> nodes = getNodesFromLine(linesIndex);
	vector<pair<double, double>> XY;
	unsigned int nodesSize = nodes.size();
	for(unsigned int nodesIndex = 0; nodesIndex < nodesSize; nodesIndex++)
	{
		unsigned int node = nodes[nodesIndex];
		pair<double, double> xy = getCoordinatesFromNodeId(node);
		XY.push_back(xy);
	}
	return XY;
}

void exitWithMessage(string s)
{
	print("Exiting for: " + s);
	exit(1);
}

pair<double, double> getCoordinates(pair<double, double> lonLat)
{
	pair<double, double> coordinates;
	coordinates.first = (lonLat.first - LON_MIN) * LON_FACT;
	coordinates.second = (lonLat.second - LAT_MIN) * LAT_FACT;
	return coordinates;
}

void preComputeLonLatTab()
{
	for(unsigned int linesIndex = 0; linesIndex < linesSize; linesIndex++)
	{
		string line = lines[linesIndex];
		if(contains(line, NODE_LOCATION))
		{
			unsigned int nodeId = convertStrToInt((split(split(line, NODE_LOCATION)[1], "\"")[0])); // not so many doc on the Internet for to_number function...
			pair<double, double> lonLat;
			lonLat.first = convertStrToDouble(split(split(line, LON_STR)[1], "\"")[0]); // does to_number does the job here ? DOUBT X - might just be imagine that this function exist (while thinking in background to to_string)
			lonLat.second = convertStrToDouble(split(split(line, LAT_STR)[1], "\"")[0]);
			lonLatTab[nodeId] = lonLat;
		}
	}
	/*vector<string> linesLonLat = getFileContent("lonLat.txt");
	unsigned int linesLonLatSize = linesLonLat.size();
	for(unsigned int linesIndex = 0; linesIndex < linesLonLatSize; linesIndex++)
	{
		string lineLonLat = linesLonLat[linesIndex];
		vector<string> lineParts = split(lineLonLat);
		lonLatTab[convertStrToInt(lineParts[0])] = {convertStrToDouble(lineParts[1]), convertStrToDouble(lineParts[2])};
	}*/
}

pair<double, double> getLonLat(unsigned int nodeId)
{
	return lonLatTab[nodeId];
}

vector<unsigned int> getNodes(pair<unsigned int, unsigned int> linesMinMax)
{
	vector<unsigned int> nodes;
	for(unsigned int linesIndex = linesMinMax.first; linesIndex < linesMinMax.second; linesIndex++)
	{
		string line = lines[linesIndex];
		if(contains(line, NODE))
		{
			nodes.push_back(convertStrToInt(split(split(line, NODE)[1], "\"/>")[0]));
		}
	}
	return nodes;
}

pair<unsigned int, unsigned int> getLines(unsigned int linesIndexDefault)
{
	pair<unsigned int, unsigned int> linesMinMax = make_pair(LINES_DEFAULT, LINES_DEFAULT); // let's not initialize with LINES_DEFAULT - bruh it's needed
	unsigned int linesIndex = linesIndexDefault;
	//print("linesIndexDefault: " + to_string(linesIndexDefault));
	while(linesIndex >= 0 && linesMinMax.first == LINES_DEFAULT)
	{
		//print("linesIndex: " + to_string(linesIndex));
		string line = lines[linesIndex];
		if(contains(line, "<node ")) return make_pair(0, 0);
		//print("line: " + line + "!" + to_string(linesIndex) + "!");
		//if(linesIndex == linesIndexDefault - 10)
		//	exit(0);
		if(contains(line, BEGIN_GRAVE_YARD))
		{
			linesMinMax.first = linesIndex;
		}
		linesIndex--;
	}
	linesIndex = linesIndexDefault;
	while(linesIndex < linesSize && linesMinMax.second == LINES_DEFAULT)
	{
		string line = lines[linesIndex];
		if(contains(line, END_GRAVE_YARD))
		{
			linesMinMax.second = linesIndex;
		}
		linesIndex++;
	}
	return linesMinMax;
}

vector<unsigned int> getNodesFromLine(unsigned int linesIndex)
{
	pair<unsigned int, unsigned int> linesMinMax = getLines(linesIndex);
	//vector<string> linesLocal = slice(); // would be less optimized
	vector<unsigned int> vec;
	if(linesMinMax.first == linesMinMax.second && linesMinMax.first == 0) return vec;
	return getNodes(/*linesLocal, */linesMinMax);
}

vector<string> getFileContent(string path)
{
	vector<string> vec;
	ifstream infile(path.c_str());
    string line;
    while(getline(infile, line))
    	vec.push_back(line);
    return vec;
}

string replaceAll(string str, const string& from, const string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

string getNbZero(unsigned short number, unsigned short numberOfDigits = 2, bool atTheEnd = false)
{
    string strNb = to_string(number);
    for(unsigned short digit = strNb.length(); digit < numberOfDigits; digit++)
        strNb = atTheEnd ? strNb + "0" : "0" + strNb;
    return strNb;
}

unsigned long long getMillis()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return (long long)tp.tv_sec * 1000L + tp.tv_usec / 1000;
}

string getDate()
{
    time_t t = time(0);
    struct tm *now = localtime(&t);

    unsigned long long ms = getMillis();

    return getNbZero(now->tm_hour) + ":" + getNbZero(now->tm_min) + ":" + getNbZero(now->tm_sec) + "." + getNbZero(ms % 1000, 3);
}

void print(string s)
{
	cout << getDate() << ": " << s << endl;
}

string WSLPath(string path) // just because I am bored to translate path by hand but this code should be run in WSL
{
    if(WSL)
        path = replaceAll(replaceAll(path, "\\", "/"), "C:/", "/mnt/c/"); // could use a simple replace for C:
    return path;
}

bool contains(string subject, string find)
{
    return subject.find(find) != string::npos;
}

vector<string> slice(vector<string> parts, unsigned int i, int j)
{
    if(j == -1)
        j = parts.size();
    vector<string> res;
    for(unsigned int part = i; part < j; part++)
        res.push_back(parts[part]);
    return res;
}

int convertStrToInt(string str) // unit truncation
{
    int number;
    sscanf(str.c_str(), "%d", &number);
    return number;
}

vector<string> split(string s, string delimiter)
{
    vector<string> toReturn;
    size_t pos = 0;
    while((pos = s.find(delimiter)) != string::npos)
    {
        toReturn.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    toReturn.push_back(s);
    return toReturn;
}

double convertStrToDouble(string str)
{
    //str = replace(str, ",", ".");
    return /*str == "N" ? SEA_BOTTOM : */atof(str.c_str());
}
