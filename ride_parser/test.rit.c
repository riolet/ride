#include "rsl/RSL_Array.h"
#include "rsl/RSL_String.h"
#include "rsl/RSL_Stream.h"
#include "rsl/rsl.h"
#include "test.rit.h"
int main(int _$$_argc_, char **_$$_argv_) {
    _$$_argc=_$$_argc_;
    _$$_argv=_$$_argv_;
	int aa;
	_$_TEMP_OBJ(_$_mptr0_1);
	_$_VARIABLE(class);
	int bb;
	_$_TEMP_OBJ(_$_mptr0_2);
	_$_VARIABLE(cc);
	/*rixc.c 559*/ aa = /* 1121 */ prthuh_$_( );
	/*rixc.c 559*/ /* 1121 */ print_$_int( /* 1178 */ aa);
	/*rixc.c 559*/ IDENT_MPTR_RAW_assign(class,/* 1121 */ A_$_A_$_( &_$_mptr0_1));
	/*rixc.c 559*/ bb = /* 1121 */ A_$_prtwat_$_int_$_int( /* 1141 */ class, /* 1178 */ 10, /* 1178 */ 20);
	/*rixc.c 559*/ IDENT_MPTR_RAW_assign(cc,String_$_stringlit("hella",&_$_mptr0_2));
	/*rixc.c 559*/ /* 1121 */ print_$_int( /* 1178 */ bb);
	/*rixc.c 559*/ /* 1121 */ print_$_String( /* 1178 */ cc);
  return 0;
}
