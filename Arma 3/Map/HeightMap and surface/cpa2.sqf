// (in EDEN Editor in Altis) use execVM "cpa2.sqf" after enabling FilePatching and put this script in A3's folder

_alg = "[CAG] ";

print =
{
    _arg = str _this;
    diag_log(_alg + _arg);
};

_size = 13000;
_precision = 75;
_c = 1.1;

diag_log "";
"##### BEGIN COPY ALGORITHM GROUND #####" call print;
"" call print;

_p = getPos player;
_px = _p select 0;
_py = _p select 1;

for "_y" from _size to -_size step -_precision do
{
	_sy = "";
	for "_x" from -_size * _c to _size * _c step _precision do
	{
		_fx = _px + _x;
		_fy = _py + _y;
		if(isOnRoad[_fx, _fy]) then
		{
			_sy = _sy + "0";
		}
		else
		{
			_sur = surfaceType[_fx, _fy];
			switch (_sur) do
			{
				// Vigesimal
				case "#GdtDirt": { _sy = _sy + "1" };
				case "#GdtGrassDry": { _sy = _sy + "2" };
				case "#GdtGrassGreen": { _sy = _sy + "3" };
				case "#GdtConcrete": { _sy = _sy + "4" };
				case "#GdtSoil": { _sy = _sy + "5" };
				case "#GdtBeach": { _sy = _sy + "6" };
				case "#GdtSeabed": { _sy = _sy + "7" };
				case "#GdtThorn": { _sy = _sy + "8" };
				case "#GdtWildField": { _sy = _sy + "9" };
				case "#GdtRock": { _sy = _sy + "A" };
				case "#GdtGrassWild": { _sy = _sy + "B" };
				case "#GdtStony": { _sy = _sy + "C" };
				case "#GdtForestPine": { _sy = _sy + "D" };
				case "#GdtMud": { _sy = _sy + "E" };
				case "#GdtStonyThistle": { _sy = _sy + "F" };
				case "#GdtMarsh": { _sy = _sy + "G" };
				case "#GdtDead": { _sy = _sy + "H" };
				case "#GdtDesert": { _sy = _sy + "I" };
				default { _sy = _sy + _sur };
			}
		}
 	};
	_sy call print;
};

"" call print;
"###### END COPY ALGORITHM GROUND ######" call print;
diag_log "";