#ifndef RANDOM_H_
#define RANDOM_H_


class CRandomGenerator
{
protected:
   static const unsigned int smRandMax = 0x7fffffff;
public:
   virtual ~CRandomGenerator() { } 
   /// seed the random number generator
   virtual void setSeed(unsigned int seed) = 0;
   /// generates a random integer on the range [0, 2^31)
   virtual int randI() = 0;
   /// generate a random F32 number on the range [0.0 to 1.0]
   virtual float randF();
   int randI(int a, int b);
   float randF(float a, float b);
};


class CTrivialRandomGenerator : public CRandomGenerator
{
protected:
   unsigned int mSeed;
public:
   CTrivialRandomGenerator(unsigned int seed = 0) { setSeed(seed); };
   virtual void setSeed(unsigned int seed);
   virtual int randI();
};

inline float CRandomGenerator::randF()
{
   return float(randI()) / float(smRandMax);
}

inline int CRandomGenerator::randI(int a, int b)
{
   if(a > b) { a ^= b; b ^= a; a ^= b; }
   return a + (randI() % (b - a + 1));
}

inline float CRandomGenerator::randF(float a, float b)
{
   if(a > b) { float t = a; a = b; b = t; }
   return a + ((b - a) * randF());
}

extern CTrivialRandomGenerator gRandom;

#endif