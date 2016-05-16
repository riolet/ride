typedef struct _$_A A;
int prthuh_$_();
int A_$_prtwat_$_int_$_int(_$_mptr * $self,int num1,int num2);
_$_mptr* A_$_destructor_$_(  _$_mptr * _$_mptr_in);
_$_mptr* A_$_A_$_(  _$_mptr * _$_mptr_in);
int prthuh_$_() {
	int i;
 	/*rixc.c 559*/ i = 5;
 	/*rixc.c 559*/ return i;
}
struct _$_A {
	_$_mptr* $super;
	BaseType * $super_;
};
int A_$_prtwat_$_int_$_int(_$_mptr * $self,int num1,int num2) {
	int a;
 	/*rixc.c 559*/ a = 10 + num1;
 	/*rixc.c 559*/ return a;
}
_$_mptr* A_$_destructor_$_(  _$_mptr * _$_mptr_in) {
 	_$_cleanup(((A *)_$_mptr_in->obj)->$super);
 	free(((A *)_$_mptr_in->obj)->$super);
 	free(((A *)_$_mptr_in->obj));
}
_$_mptr* A_$_A_$_(  _$_mptr * _$_mptr_in) {
	_$_HEAP_VARIABLE(_$_mptr0);
 	A * $self_ = calloc(1, sizeof(A));
_$_mptr * $self = _$_returnAppointer(_$_mptr_in,$self_,A_$_destructor_$_);
 	$self_->$super= BaseType_$_BaseType_$_(_$_mptr0);
 	$self_->$super_= $self_->$super->obj;
 	return $self;
}
