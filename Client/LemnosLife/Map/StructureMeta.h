#ifndef DEF_STRUCTURE_META
#define DEF_STRUCTURE_META

class StructureMeta
{
    public:
        StructureMeta(unsigned short, double[], unsigned short);
        void render();
        double* getCoordinates();
    private:
        unsigned short int m_id;
        double m_coordinates[3];
        unsigned short m_direction;
};

#endif