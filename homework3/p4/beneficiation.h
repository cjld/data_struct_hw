#ifndef _BENEFICIATION_H_

#ifdef __cplusplus
extern "C"
{
#endif

    int GetNumOfOre(void);

    void Measure(int a, int b, int c, int d,
                int *wa, int *wb, int *wc, int *wd);

    void Report(int no, int rank);

#ifdef __cplusplus
}
#endif

#endif //_BENEFICIATION_H_
