#include "RandomPoint.h"
#include "../Logger/logger.h"
#include "../2D/vector2d/h"
using namespace std;

/// GENERATING RANDOM POINT IN 2D WITHIN A GIVEN AREA

// multiple cases:
// 1. rectangle (easy: random x, random y) - constant
// 2. area (don't know if convex or concave):
//   2.1. in rectangle and check if point is in the area (could potentially takes infinite time but the probability to do so is "zero" ^^)
//   2.2. in convex envelop and check if point is in (like 2.1. case but the convex envelop may reduce fail points)
// 3. convex: "moderate" consider barycenter as an origin, generate n vectors for the n points of the convex and generate random subvector (generate random real between 0 and 1 for each vector and multiply by this latter) - constant
// 4. concave: "hard" split into convex sets with algorithm like Delaunay's triangulation (because a triangle is convex, do better algorithms for this purpose of spliting convex set into concave sets exist ?)

// adaptation d'un corrigé de DM optionnel de 5/2 (vu personnellement (Ben) en 3/2) de Python vers C++ (merci à Jérome Nizon ancien normalien et qui fut mon professeur de maths en MPSI et d'IPT en MP*)

/// TODO: to finish

// shouldn't be used for the moment so don't code it completely in C++
/*
void afficheTriangle(vector<Vector2D> l, vector<vector<Vector2D>> t, vector<> env)
{
    // permet d'afficher une triangulation de Delaunay: l liste des points, t liste des triangles
    // env est l'enveloppe convexe, non affichée si l'argument est []
    plt.plot([l[i][0] for i in range(len(l))],[l[i][1] for i in range(len(l))],"o",color="black")
    for x in t:
        tab = [x[-1]] + x
        plt.plot([tab[i][0] for i in range(len(tab))], [tab[i][1] for i in range(len(tab))],color="blue")
    for x in env:
        plt.plot([x[0][0], x[1][0]], [x[0][1], x[1][1]], color = "cyan")
    plt.show()
}
*/

// vector<Vector2D> l {Vector2D(10, 10), Vector2D(50, 30), ...};
// vector<vector<Vector2D>> t; // better way to initialize here ?
// vector<Vector2D> t0 {Vector2D(10, 10), Vector2D(50, 30), Vector2D(20, 10)};
// t.push_back(t0);
// ...
// afficheTriangle(l, t);

double det(double a, double b, double c, double d) // already coded ?
{
    return a * d - b * c;
}

Vector2D angle(Vector2D PI, Vector2D PJ, vector<Vector2D> l, short sens)
{
    // détermine le point le plus proche de PI PJ dans le sens trigo (sens = 1) ou non un point est candidat si le sinus de l'angle a le signe de sens l'algo renvoie PI s'il n'en trouve pas parmi les candidats, l'angle est maximal si le cos est minimal
    double xk = PI.X, yk = PI.Y,
           sck = 2;
	unsigned int lSize = l.size();
    for(unsigned int lIndex = 0; lIndex < lSize; lIndex++)
	{
		Vector2D z = l[lIndex];
		double xz = z.X, yz = z.Y,
               a = PI.X - xz, b = PI.Y - yz, c = PK.X - xz, d = PJ.Y - yz;
        if(sens * det(a, b, c, d) > 0) // on compare des entiers ici!
		{
			// is sc really a double ? not just an integer ?
            double sc = (a * c + b * d) / (((a ** 2 + b ** 2) * (c ** 2 + d ** 2)) ** (1 / 2));
            if(sc < sck)
			{
                xk = z.X;
				yk = z.Y;
                sck = sc;
			}
		}
	}
    return Vector2D(xk, yk);
}

/*vector<Vector2D> sorted(vector<Vector2D> abc) // should make a general function likewise could also be used by inserec function
{
	Vector2D a = abc[0], b = abc[1], c = abc[2];
	vector<Vector2D> res; // how to return in one line a new vector ?
	if(a < b)
	{
		if(b < c)
		{
			res.push_back();
		}
	}
	else
	{
		
	}
	return res;
}*/

vector<Vector2D> sorted(vector<Vector2D> toSort) // TODO: should optimize
{
	
}

void insere(vector<vector<Vector2D>> l, Vector2D a, Vector2D b, Vector2D c)
{
    // print(a, b, c) // enlever le commentaire pour comprendre pas à pas la construction
    // insere le nouveau triangle [a, b, c] dans la liste l s'il n'est pas déjà présent pour simplifier la recherche, on ordonne a, b, c et on utilise les fonctions python
    x, y, z = sorted([a, b, c])
    if [x, y, z] not in l:
        l.append([x, y, z])
}
        
void inserec(vector<vector<Vector2D>> l, Vector2D a, Vector2D b)
{
    // insere le nouveau segmenet dans l'enveloppe convexe l
    x, y = min(a, b), max(a, b)
    if [x, y] not in l:
        l.append([x, y])
}
        
Vector2D proche(PI, l)
{
    // on détermine le point de l le plus proche de PI (d minimal)
    double d = -1;
	// could initialize to the maximum or first distance and remove the check statement in the following if
    Vector2D PJ; // warning not initialized ?
	
	unsigned int lSize = l.size();
	for(unsigned int lIndex = 0; lIndex < lSize; lIndex++)
    {
		Vector2D x = l[lIndex];
        double nd = (x.X - PI.X) ** 2 + (x.Y - PI.Y) ** 2;
        if(x != PI and (d < 0 or nd < d)) // != operator doesn't seem to be coded
		{
            d = nd;
            PJ = x;
		}
    }
	return PJ;
}
    
pair<vector<vector<Vector2D>>, vector<vector<Vector2D>>> delaunay(vector<Vector2D> l)
{
	unsigned int lSize = l.size();
    if(lSize < 3) // is impossible by code ?
	{
        print("Il faut au moins 3 points !");
    }
    vector<vector<Vector2D>> triangle, // liste de triangulation sans redondance
							 enveloppe; // enveloppe convexe en prime (better algorithms to compute it faster ?)
    for(unsigned int lIndex = 0; lIndex < lSize; lIndex++):
    {
		Vector2D PI = l[lIndex], PJ = proche(PI, l),PH = PJ;
		// on passe donc en revue tous les points de la liste
        //PJ est donc le point le plus proche de PI trouvé 
        bool pasFini = true; // passera à false quand on aura fini le traitement de PI
        short sens = 1;  // on commence par le sens trigo
        while(pasFini)
		{
            PK = angle(PI, PH, l, sens);
            if(PK == PJ) // need to code == operator for Vector2D // on tombe sur PJ donc on a fait un tour complet
            {
				insere(triangle, PI, PH, PJ);
                pasFini = false;
            }
			else if(PK == PI)  // on ne trouve pas de points: on est sur le bord
            {
				inserec(enveloppe, PI, PH);
                if(sens == -1) // si on n'est pas dans le sens trigo c'est fini
				{
                    pasFini = false;
				}
                else //sinon on inverse le sens et on repart de PJ
				{
                    sens = -1;
                    PH = PJ;
				}
            }
			else // cas général: on a trouvé un triangle à ajouter
            {
				insere(triangle, PI, PH, PK);
                PH = PK;
			}
		}
	}
    return make_pair(triangle, enveloppe);
}

// pair<vector<vector<Vector2D>>, vector<vector<Vector2D>>> triangleEnveloppe = delaunay(l);
// afficheTriangle(l, triangleEnveloppe.first, triangleEnveloppe.second);
