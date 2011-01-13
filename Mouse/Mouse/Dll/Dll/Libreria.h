#ifndef LIBRERIA
#define LIBRERIA extern "C" __declspec(dllimport)
#endif

LIBRERIA void ApplicaOnMouse(bool check, int value, int s1, int s2, int s3);
LIBRERIA void AskMouse(bool &check, int &value, int &s1, int &s2, int &s3);
LIBRERIA bool check();