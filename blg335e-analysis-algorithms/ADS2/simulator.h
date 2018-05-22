#ifndef SIMULATOR_H
#define SIMULATOR_H


class Simulator
{
    public:
        void simulate(int m, float p);
    private:
        int selectRandomInstance(int numberOfInstances);
        bool isUpdateOperation(float updateProbability);
};

#endif // SIMULATOR_H
