_alg = "[CP-ALG] "; 
 
print ={ 
    _arg = _this; 
    diag_log (_alg + _arg); 
}; 
 
diag_log ""; 
"##### BEGIN COPY ALGORITHM #####" call print; 
"" call print; 
 
"CURSOR TARGET" call print; 
("Model: " + str (getModelInfo cursorObject select 0)) call print; 
("Pos: " + str getPos cursorObject) call print; 
("Dir: " + str getDir cursorObject) call print; 
 
"" call print; 
"###### END COPY ALGORITHM ######" call print; 
diag_log "";
