#include "CException.h"

/* \brief permet de faire des tests et de générer des erreurs*/
template<class Mtype>
class CHandle_Error 
{
public:
	static void handle_Egalite(<Mtype> mValeurATester, <Mtype> mValeurLeveExcption, unsigned int Error);
	static void handle_Different(<Mtype> mValeurATester, <Mtype> mValeurLeveExcption, unsigned int Error);
	static void handle_Inferieur(Mtype mValeurATester, MType mValeurLeveExcption, unsigned int Error);
	static void handle_Superieur(Mtype mValeurATester, MType mValeurLeveExcption, unsigned int Error);
};

template<class Mtype>
inline void CHandle_Error<Mtype>::handle_Egalite(<Mtype> mValeurATester, <Mtype> mValeurLeveExcption, unsigned int Error)
{
	if (mValeurATester == mValeurLeveExcption)
	{
		throw(new CException(Error));
	}
}
