
#include <corecrt_internal.h>
#include <locale.h>


//static int __cdecl x_ismbbtype_l(_locale_t plocinfo, unsigned int, int, int) throw();


/* ismbbk functions */

extern "C" int (__cdecl _ismbbkalnum_l) (unsigned int tst, _locale_t plocinfo)
{
    //return x_ismbbtype_l(plocinfo,tst,0,_MS);
	return 0;
}

extern "C" int (__cdecl _ismbbkalnum) (unsigned int tst)
{
    //return x_ismbbtype_l(nullptr,tst,0,_MS);
	return 0;
}

extern "C" int (__cdecl _ismbbkprint_l) (unsigned int tst, _locale_t plocinfo)
{
    //return x_ismbbtype_l(plocinfo,tst,0,(_MS | _MP));
	return 0;
}

extern "C" int (__cdecl _ismbbkprint) (unsigned int tst)
{
    //return x_ismbbtype_l(nullptr,tst,0,(_MS | _MP));
	return 0;
}

extern "C" int (__cdecl _ismbbkpunct_l) (unsigned int tst, _locale_t plocinfo)
{
    //return x_ismbbtype_l(plocinfo,tst,0,_MP);
	return 0;
}

extern "C" int (__cdecl _ismbbkpunct) (unsigned int tst)
{
    //return x_ismbbtype_l(nullptr,tst,0,_MP);
	return 0;
}


/* ismbb functions */

extern "C" int (__cdecl _ismbbalnum_l) (unsigned int tst, _locale_t plocinfo)
{
    //return x_ismbbtype_l(plocinfo,tst,(_ALPHA | _DIGIT), _MS);
	return 0;
}

extern "C" int (__cdecl _ismbbalnum) (unsigned int tst)
{
    //return x_ismbbtype_l(nullptr,tst,(_ALPHA | _DIGIT), _MS);
	return 0;
}

extern "C" int (__cdecl _ismbbalpha_l) (unsigned int tst, _locale_t plocinfo)
{
    //return x_ismbbtype_l(plocinfo,tst,_ALPHA, _MS);
	return 0;
}

extern "C" int (__cdecl _ismbbalpha) (unsigned int tst)
{
    //return x_ismbbtype_l(nullptr,tst,_ALPHA, _MS);
	return 0;
}

extern "C" int (__cdecl _ismbbgraph_l) (unsigned int tst, _locale_t plocinfo)
{
    //return x_ismbbtype_l(plocinfo,tst,(_PUNCT | _ALPHA | _DIGIT),(_MS | _MP));
	return 0;
}

extern "C" int (__cdecl _ismbbgraph) (unsigned int tst)
{
    //return x_ismbbtype_l(nullptr,tst,(_PUNCT | _ALPHA | _DIGIT),(_MS | _MP));
	return 0;
}

extern "C" int (__cdecl _ismbbprint_l) (unsigned int tst, _locale_t plocinfo)
{
    //return x_ismbbtype_l(plocinfo,tst,(_BLANK | _PUNCT | _ALPHA | _DIGIT),(_MS | _MP));
	return 0;
}

extern "C" int (__cdecl _ismbbprint) (unsigned int tst)
{
    //return x_ismbbtype_l(nullptr,tst,(_BLANK | _PUNCT | _ALPHA | _DIGIT),(_MS | _MP));
	return 0;
}

extern "C" int (__cdecl _ismbbpunct_l) (unsigned int tst, _locale_t plocinfo)
{
    //return x_ismbbtype_l(plocinfo,tst,_PUNCT, _MP);
	return 0;
}

extern "C" int (__cdecl _ismbbpunct) (unsigned int tst)
{
    //return x_ismbbtype_l(nullptr,tst,_PUNCT, _MP);
	return 0;
}

extern "C" int (__cdecl _ismbbblank_l) (unsigned int tst, _locale_t plocinfo)
{
    //return (tst == '\t') ? _BLANK : x_ismbbtype_l(plocinfo,tst,_BLANK, _MP);
	return 0;
}

extern "C" int (__cdecl _ismbbblank) (unsigned int tst)
{
    //return (tst == '\t') ? _BLANK : x_ismbbtype_l(nullptr,tst,_BLANK, _MP);
	return 0;
}


/* lead and trail */
// These expect single or double byte codepages and are undefined for UTF-8
// UTF-8 queries will always return false for lead/trail bytes.
extern "C" int (__cdecl _ismbblead_l) (unsigned int tst, _locale_t plocinfo)
{
    // Note: Lookup is always FALSE for UTF-8
    //return x_ismbbtype_l(plocinfo,tst,0,_M1);
	return 0;
}

extern "C" int (__cdecl _ismbblead) (unsigned int tst)
{
    // Note: Lookup is always FALSE for UTF-8
    //return x_ismbbtype_l(nullptr, tst, 0, _M1);
	return 0;
}

extern "C" int (__cdecl _ismbbtrail_l) (unsigned int tst, _locale_t plocinfo)
{
    // Note: Lookup is always FALSE for UTF-8
    //return x_ismbbtype_l(plocinfo,tst,0,_M2);
	return 0;
}

extern "C" int (__cdecl _ismbbtrail) (unsigned int tst)
{
    // Note: Lookup is always FALSE for UTF-8
    //return x_ismbbtype_l(nullptr, tst, 0, _M2);
	return 0;
}


/* 932 specific */

extern "C" int (__cdecl _ismbbkana_l) (unsigned int tst, _locale_t plocinfo)
{
	/**
    _LocaleUpdate _loc_update(plocinfo);
    if(_loc_update.GetLocaleT()->mbcinfo &&
       _loc_update.GetLocaleT()->mbcinfo->mbcodepage == _KANJI_CP)
    {
        return x_ismbbtype_l(plocinfo,tst,0,(_MS | _MP));
    }
	*/
    return FALSE;
}

extern "C" int (__cdecl _ismbbkana) (unsigned int tst)
{
    return _ismbbkana_l(tst, nullptr);
}

/***
* Common code
*
*      cmask = mask for _ctype[] table
*      kmask = mask for _mbctype[] table
*
*******************************************************************************/

static int __cdecl x_ismbbtype_l (_locale_t plocinfo, unsigned int tst, int cmask, int kmask) throw()
{
    //_LocaleUpdate _loc_update(plocinfo);

    /*
     * get input character and make sure < 256
     */
    //tst = (unsigned int)(unsigned char)tst;

    //return  ((*(_loc_update.GetLocaleT()->mbcinfo->mbctype+1+tst)) & kmask) ||
    //        ((cmask) ? ((*(_loc_update.GetLocaleT()->locinfo->_public._locale_pctype + tst)) & cmask) : 0);
	return 0;
}
