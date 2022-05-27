#include "tst_manzhuk.h"
#include "manzhuk/manzhuk.h"

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <QObject>
#include <QtTest/qtest.h>

/*class tst_ManZhuk : public QObject
{
    Q_OBJECT
public:
    explicit tst_ManZhuk();

private slots:
    void initTestCase();
    void tstDuffing();

private:
    //task001 task002 - Duffing equation
    inline friend void fcttask001(double z[],double px[],double f[],double rj1[],double rj2[],int n,int m,double t,double h,int ncon,int *nbad,int ip[]);
    inline friend void outtask001(double z[],double px[],int n,int m,double t,double t0,double tk,double h,double *tkv,int ncon,int ip[]);

private:
    // Common variables for manzhuk ODE systems solver
    double rj1[2500], rj2[2500];
    double z[50], px[50], z1[50], xp1[50], f[50], t, t0, tk, h, hmn, hmx, eps, tkv;
    int n, nm, m, ncon, nbad, ier, ip[10000];
    FILE *f01,*f02;
    // Tasks&tests for ODE sets
    int i;
    double pi4, om, tstartp, tendp, deltatp, tkp;
    double mu0, mu1;
    double c1, c2, l, r;
    double mu;
    double c01, c02, c03, l01, l02, l03, a;
    double b, g, a1, a11, a12, a13, a21, a22, a23, a31, a32, a33;
}; */

tst_ManZhuk ManZhukTest;

void global_fcttask(double z[],double px[],double f[],double rj1[],double rj2[],int n,int m,double t,double h,int ncon,int *nbad,int ip[]) {
    switch (ManZhukTest.m_currentTest) {
        case Duffing:
        ManZhukTest.fcttask001(z, px, f, rj1, rj2, n, m, t, h, ncon, nbad, ip);
        break;
        default:
        break;
    }
}

void global_outtask(double z[],double px[],int n,int m,double t,double t0,double tk,double h,double *tkv,int ncon,int ip[]) {
    switch (ManZhukTest.m_currentTest) {
        case Duffing:
        ManZhukTest.outtask001(z, px, n, m, t, t0, tk, h, tkv, ncon, ip);
        break;
        default:
        break;
    }
}

tst_ManZhuk::tst_ManZhuk()
{
}

void tst_ManZhuk::initTestCase()
{
//#if QT_CONFIG(library)
    /*
     * Set custom path since CI doesn't install test plugins
     */
    //QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath()
    //                                 + QStringLiteral("/../../../plugins"));
//#ifdef Q_OS_WIN
    //QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath()
    //                                 + QStringLiteral("/../../../../plugins"));
//#endif
//#endif // QT_CONFIG(library)
    /*bus = QCanBus::instance();
    QVERIFY(bus);
    QCanBus *sameInstance = QCanBus::instance();
    QCOMPARE(bus, sameInstance);*/
}

void tst_ManZhuk::tstDuffing()
{
    m_currentTest = Duffing;
    f01=fopen("task001.rez","wt");
    f02=fopen("grtask001.rez","wt");
    om=1e0;
    pi4=atan(1.0);
    eps=1e-3;
    fprintf(f01,"        relative tolerance - eps=%e pi4=%e\n",eps,pi4);
    nm=1;
    fprintf(f01,"        number of method - nm=%d\n",nm);
    t0=0e0;
    tk=250e0;
    tstartp=240e0;//time for start printing
    tendp=245e0;//time for end printing
    deltatp=1e0;//step for printing
    fprintf(f01, " tstartp=%e deltatp=%e tendp=%e\n", tstartp, deltatp, tendp);
    hmn=1e-10;
    hmx=tk/10e0;
    n=2;
    m=2;
    z[1]=0e0;
    z[2]=0e0;
    z1[1]=fabs(z[1]);
    z1[2]=fabs(z[2]);

    manzhuk(z, px, z1, xp1, f, rj1, rj2, t, t0,tk, h, hmn, hmx, eps,
            &tkv, n, m, nm, ncon, &nbad, &ier, ip, global_fcttask, global_outtask);

    fprintf(f01,"ier= %d \n",ier);
    printf("ier= %d \n",ier);
    for(i=1;i<=16;i++)fprintf(f01,"%d ",ip[i]);
    fprintf(f01,"\n");
    for(i=1;i<=16;i++)printf("%d ",ip[i]);
    printf("\n");
    fclose(f01);
    fclose(f02);

}

//task001 task002 - Duffing equation
void tst_ManZhuk::fcttask001(double z[],double px[],double f[],double rj1[],double rj2[],int n,int m,double t,double h,int ncon,int *nbad,int ip[])
{
    f[1]=px[1]-z[2];
        rj1[1*n+1]=1e0;
        rj2[1*n+2]=-1e0;
    f[2]=px[2]-0.5*z[1]+0.25e0*z[2]+0.5e0*z[1]*z[1]*z[1]-0.3*cos(om*t);
        rj1[2*n+2]=1e0;
        rj2[2*n+1]=-0.5e0+1.5e0*z[1]*z[1];
        rj2[2*n+2]=0.25e0;
    return;
}
void tst_ManZhuk::outtask001(double z[], double px[], int n, int m, double t, double t0,
                             double tk, double h, double *tkv, int ncon, int ip[])
{
    if (ncon == 0) fprintf(f01,"           Duffing equations, t, x1, x2, px1, px2\n");
    if (ncon == 0) fprintf(f02,"           Duffing equations, t, x1, x2, px1, px2\n");
    // Start print of tabulation results
    if (ncon == 0) tkp = deltatp;
    if (deltatp == 0) goto m20;
    if (t <= tkp) goto m10;
    tkp = tkp + deltatp;

m10:
    if ((tkp < *tkv) && (*tkv >= t)) *tkv = tkp;
    if (t < tstartp) goto m20;
    if (t > tendp) goto m20;
    if (t == *tkv) fprintf(f01, "  %e   %e  %e  %e  %e\n", t, z[1], z[2], px[1], px[2]);

m20:
    // End print of tabulation results
    fprintf(f02, "  %e   %e  %e  %e  %e\n", t, z[1], z[2], px[1], px[2]);
    return;
}

QTEST_MAIN(tst_ManZhuk)

//#include "tst_manzhuk.moc"
