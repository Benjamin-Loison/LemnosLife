public class Main
{
    public static void main(String[] args)
    {
        String[] a3Locations = {"[16761.9,15491.2,0]", "[16761.9,15491.2,0]"};
        byte a3LocationsLength = (byte)a3Locations.length;
        if(a3LocationsLength != 2)
        {
            System.out.println("2 args are needed !");
            System.exit(1);
        }
        
        byte dimension = (byte)a3Locations[0].split(",").length;
        double[][] coordinates = new double[a3LocationsLength][dimension];
        for(byte a3LocationsIndex = 0; a3LocationsIndex < a3LocationsLength; a3LocationsIndex++)
        {
            String a3Location = a3Locations[a3LocationsIndex];
            a3Location = a3Location.substring(1, a3Location.length() - 1);
            String[] a3LocationParts = a3Location.split(",");
            for(byte a3LocationPartsIndex = 0; a3LocationPartsIndex < a3LocationParts.length; a3LocationPartsIndex++)
            {
                coordinates[a3LocationsIndex][a3LocationPartsIndex] = Double.parseDouble(a3LocationParts[a3LocationPartsIndex]);
            }
        }
        
        double sumDistanceDimension = 0;
        for(byte dimensionIndex = 0; dimensionIndex < dimension; dimensionIndex++)
        {
            double totalDimension = coordinates[0][dimensionIndex];
            for(byte a3LocationsIndex = 1; a3LocationsIndex < a3LocationsLength; a3LocationsIndex++)
            {
                totalDimension -= coordinates[a3LocationsIndex][dimensionIndex];
            }
            sumDistanceDimension += Math.pow(totalDimension, 2);
        }
        
        System.out.println(Math.sqrt(sumDistanceDimension));
    }
}