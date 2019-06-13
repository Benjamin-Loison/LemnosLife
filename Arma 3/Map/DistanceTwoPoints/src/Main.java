public class Main
{
    public static void main(String[] args)
    {
        double lat1 = 39.9, lat2 = 39.9; // degrees
        double long1 = 25.153, long2 = 25.154; // degrees
        double latitude1 = lat1 * Math.PI / 180, latitude2 = lat2 * Math.PI / 180; // rad
        double longitude1 = long1 * Math.PI / 180, longitude2 = long2 * Math.PI / 180; // rad
        double earthRadius = 6371; // km
        double distance = earthRadius * Math.acos(Math.cos(latitude1) * Math.cos(latitude2) * Math.cos(longitude2 - longitude1) + Math.sin(latitude1) * Math.sin(latitude2)); // km
    }
}
