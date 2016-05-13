
#include <string>
#include <vector>
#include "datastruct.h"

#ifndef UTIL_H
#define UTIL_H




using namespace std;




const string attr[400] = {"Vol", "Cur", "Pow", "Tem", "Hum", "Lig", "Red", "Bla", "Yel", "Whi",
												 "Ora", "Gre", "Tup", "Blu", "Gra", "App", "Bal", "Pea", "Sea", "All",
												 "Fra", "Get", "Put", "Nod", "Ptr", "Add", "Str", "Tex", "Vec", "Arr",
												 "Baa", "Bcc", "Bdd", "Bee", "Bff", "Bgg", "Bhh", "Bii", "Bjj", "Bkk",
												 "Bll", "Bmm", "Bnn", "Boo", "Bpp", "Bqq", "Brr", "Bss", "Btt", "Buu",
												 "Bvv", "Bww", "Bxx", "Byy", "Bzz", "Caa", "Cbb", "Cdd", "Cee", "Cff",
												 "Cgg", "Chh", "Cii", "Cjj", "Ckk", "Cll", "Cmm", "Cnn", "Coo", "Cpp",
												 "Cqq", "Crr", "Css", "CTT", "Cuu", "Cvv", "Cww", "Cxx", "Cyy", "Czz",
												 "Daa", "Dbb", "Dcc", "Dee", "Dff", "Dgg", "Dhh", "Dii", "Djj", "Dkk",
												 "Dll", "Dmm", "Dnn", "Doo", "Dpp", "Dqq", "Drr", "Dss", "Dtt", "Duu",
												 "Dvv", "Dww", "Dxx", "Dyy", "Dzz", "Eaa", "Ebb", "Ecc", "Edd", "Eff",
												 "Egg", "Ehh", "Eii", "Ejj", "Ekk", "Ell", "Emm", "Enn", "Eoo", "Epp",
												 "Eqq", "Err", "Ess", "Ett", "Euu", "Evv", "Eww", "Exx", "Eyy", "Ezz",
												 "Faa", "Fbb", "Fcc", "Fdd", "Fee", "Fgg", "Fhh", "Fii", "Fjj", "Fkk",
												 "Fll", "Fmm", "Fnn", "Foo", "Fpp", "Fqq", "Frr", "Fss", "Ftt", "Fuu",
												 "Fvv", "Fww", "Fxx", "Fyy", "Fzz", "Gaa", "Gbb", "Gcc", "Gdd", "Gee",
												 "Gff", "Ghh", "Gii", "Gjj", "Gkk", "Gll", "Gmm", "Gnn", "Goo", "Gpp",
												 "Gqq", "Grr", "Gss", "Gtt", "Guu", "Gvv", "Gww", "Gxx", "Gyy", "Gzz",
												 "Haa", "Hbb", "Hcc", "Hdd", "Hee", "Hff", "Hgg", "Hii", "Hjj", "Hkk",
												 "Hll", "Hmm", "Hnn", "Hoo", "Hpp", "Hqq", "Hrr", "Hss", "Htt", "Huu",
												 "Hvv", "Hww", "Hxx", "Hyy", "Hzz", "Iaa", "Ibb", "Icc", "Idd", "Iee",
												 "Iff", "Igg", "Ihh", "Ijj", "Ikk", "Ill", "Imm", "Inn", "Ioo", "Ipp",
												 "Iqq", "Irr", "Iss", "Itt", "Iuu", "Ivv", "Iww", "Ixx", "Iyy", "Izz",
												 "Jaa", "Jbb", "Jcc", "Jdd", "Jee", "Jff", "Jgg", "Jhh", "Jii", "Jkk",
												 "Jll", "Jmm", "Jnn", "Joo", "Jpp", "Jqq", "Jrr", "Jss", "Jtt", "Juu",
												 "Jvv", "Jww", "Jxx", "Jyy", "Jzz", "Kaa", "Kbb", "Kcc", "Kdd", "Kee",
												 "Kff", "Kgg", "Khh", "Kii", "Kjj", "Kll", "Kmm", "Knn", "Koo", "Kpp",
												 "Kqq", "Krr", "Kss", "Ktt", "Kuu", "Kvv", "Kww", "Kxx", "Kyy", "Kzz",
												 "Laa", "Lbb", "Lcc", "Ldd", "Lee", "Lff", "Lgg", "Lhh", "Lii", "Ljj",
												 "Lkk", "Lmm", "Lnn", "Loo", "Lpp", "Lqq", "Lrr", "Lss", "Ltt", "Luu",
												 "Lvv", "Lww", "Lxx", "Lyy", "Lzz", "Maa", "Mbb", "Mcc", "Mdd", "Mee",
												 "Mff", "Mgg", "Mhh", "Mii", "Mjj", "Mkk", "Mll", "Mnn", "Moo", "Mpp",
												 "Mqq", "Mrr", "Mss", "Mtt", "Muu", "Mvv", "Mww", "Mxx", "Myy", "Mzz",
												 "Naa", "Nbb", "Ncc", "Ndd", "Nee", "Nff", "Ngg", "Nhh", "Nii", "Njj",
												 "Nkk", "Nll", "Nmm", "Noo", "Npp", "Nqq", "Nrr", "Nss", "Ntt", "Nuu",
                                                "Nvv", "Nww", "Nxx", "Nyy", "Nzz", "Oaa", "Obb", "Occ", "Odd", "Oee",
												 "Off", "Ogg", "Ohh", "Oii", "Ojj", "Okk", "Oll", "Omm", "Onn", "Opp",
												 "Oqq", "Orr", "Oss", "Ott", "Ouu", "Ovv", "Oww", "Oxx", "Oyy", "Ozz",
												 "Paa", "Pbb", "Pcc", "Pdd", "Pee", "Pff", "Pgg", "Phh", "Pii", "Pjj",
												 "Pkk", "Pll", "Pmm", "Pnn", "Poo", "Pqq", "Prr", "Pss", "Ptt", "Puu"};



class Util
{

public:

    static std::string RemoveBlank (std::string str);
    static void Maopao(vector<int> &vec);
    static string Double2String (double value);
    static double String2Double (string str);
	static bool CheckExist (int value, vector<int> array);

	static Sub ExtractSub (string text);
    static Pub ExtractPub (string text);
	static int Name2Index (string str);

	static string GenerateSub_normal (int items, int attrs, double width, double alp);
    static string GeneratePub (int attrs);

	static string SubDis (int items, int attrs, double width, double zipf);
    static string PubDis (int attrs);


};

#endif

