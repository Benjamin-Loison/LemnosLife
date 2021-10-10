if(configurationData["gameplay"] == GAMEPLAY_CITERP)
{
    if(startsWithIgnoreCase(message, "couvre-feu"))
    {
        if(user->getPoliceLevel() > CIVILIAN_POLICE)
        {
            vector<Vector3D> vecs = {Vector3D(0, 0, 0), Vector3D(100, 100, 0)};
            unsigned short vecsSize = vecs.size();
            for(unsigned short vecsIndex = 0; vecsIndex < vecsSize; vecsIndex++)
            {
                Vector3D vec = vecs[vecsIndex];
                sendAllUsers("Sound wall " + toString(vec, ","));
            }
        }
        else
        {
            sendAllBridgesServChat("You must be %s to use this command !`" + getAdminGrade(ADJOINT_POLICE), true, ip, port);
        }
    }
}
