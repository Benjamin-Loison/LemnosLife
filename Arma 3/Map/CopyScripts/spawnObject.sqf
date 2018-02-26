_pos = player getRelPos [10, 0];
// 10 is on an horizontal axe
_path = "a3\structures_f\ind\factory\factory_conv2_f";
// just above: name of the structure (with the path and without the file extension)
_path = _path + ".p3d";
_obj = createSimpleObject [_path, _pos]; 
_obj setPos (_pos vectorAdd (getPosWorld _obj vectorDiff (_obj modelToWorld [0,0,-40])));
// -40 is the vertical postion (- means up)
