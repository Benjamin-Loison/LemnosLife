_alg = "[CP-ALG] "; 
 
print ={ 
    _arg = _this; 
    diag_log (_alg + _arg); 
}; 
 
diag_log ""; 
"##### BEGIN COPY ALGORITHM #####" call print; 
"" call print; 

_range = 50000;
_pos = getPos player;

("Map: " + worldName) call print;
("Loading nearestTerrainObjects with radius (m): " +  str _range + " at position (from bottom left on the map): " + str _pos) call print; 
_objs = nearestTerrainObjects[_pos, [], _range]; 
"Loading finished !" call print; 
"" call print; 
 
 
infoObj ={ 
 ("Model: " + str (getModelInfo _this select 1)) call print; 
 _pos = getPos _this; 
 ("Pos: " + str (_pos select 0) + " " + str (_pos select 1) + " " + str (_pos select 2)) call print; 
 ("Dir: " + str getDir _this) call print; 
    "" call print; 
}; 
 
for [{_i=0}, {_i < count _objs}, {_i=_i+1}] do 
{ 
    (_objs select _i) call infoObj; 
}; 
 
"" call print; 
"###### END COPY ALGORITHM ######" call print; 
diag_log "";
