#pragma once

//**********************************
// Libero Global MACRO definitions:
//**********************************
#define UPAR(x) (x)
#define SAFEDELETE(x) if (x){ delete x; x = nullptr;}

#define WIN32_LEAN_AND_MEAN

//*********************************************************************************
// Deleting the rule of five of a given class
#define ROFDEL(x) x(const x&)=delete; \
					x(x&&)=delete; \
					x& operator=(const x&)=delete; \
					x& operator=(x&&)=delete;
//*********************************************************************************

//*********************************************************************************
// EZ Declaration macros
#define DefGetRef(Type, Var, As) Type& Get##As##Ref() {return Var;}
#define DefGet(Type, Var, As) const Type Get##As() const{return Var;}
#define DefSet(Type, Var, As) void Set##As(const Type& value) {##Var = value;}
#define DefGetSet(Type, Var, As) DefGet(Type, Var, As); DefSet(Type, Var, As);
//*********************************************************************************

template <typename P>
void SafeDelete(P pointer)
{
	delete pointer;
	pointer = nullptr;
}