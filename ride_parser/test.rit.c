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
	/*rixc.c 557*/ aa = /* 1119 */ prthuh_$_( );
	/*rixc.c 557*/ /* 1119 */ print_$_int( /* 1176 */ aa);
	/*rixc.c 557*/ IDENT_MPTR_RAW_assign(class,/* 1119 */ A_$_A_$_( &_$_mptr0_1));
	/*rixc.c 557*/ bb = /* 1119 */ A_$_prtwat_$_int_$_int( /* 1139 */ class, /* 1176 */ 10, /* 1176 */ 20);
	/*rixc.c 557*/ IDENT_MPTR_RAW_assign(cc,String_$_stringlit("hella",&_$_mptr0_2));
	/*rixc.c 557*/ /* 1119 */ print_$_int( /* 1176 */ bb);
	/*rixc.c 557*/ /* 1119 */ print_$_String( /* 1176 */ cc);
  return 0;
}
