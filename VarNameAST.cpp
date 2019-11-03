#include "VarNameAST.h"


VarNameAST::VarNameAST(IdentifierAST* identifier)// type = 0
{
	this->type = 0;
	this->identifier = identifier;
}

VarNameAST::VarNameAST(VarNameAST* left, ExpAST* intExp)//type = 1
{
	this->type = 1;
	this->left = left;
	this->intExp = intExp;
}

VarNameAST::VarNameAST(VarNameAST* left, VarNameAST* right, int type)// type = 2   3
{
	this->type = type;
	this->left = left;
	this->right = right;
}

VarNameAST::VarNameAST(ExpAST* exp)
{
	this->type = 4;
	this->exp = exp;
}

void VarNameAST::setType(zx::Type varType)
{
	this->varType = varType;
}

void VarNameAST::setFinalToType(zx::Type finalToType)
{
	this->finalToType = finalToType;
}

void VarNameAST::setPointerNum(int pointerNum)
{
	this->pointerNum = pointerNum;
}

void VarNameAST::setStructName(string name)
{
	this->structName = name;
}

VarNameAST::~VarNameAST()
{
	if (this->left != nullptr)
	{
		delete this->left;
	}
	if (this->right != nullptr)
	{
		delete this->right;
	}
	if (this->intExp != nullptr)
	{
		delete this->intExp;
	}
	if (this->identifier != nullptr)
	{
		delete this->identifier;
	}
	if (this->exp != nullptr)
	{
		delete this->exp;
	}
}

string VarNameAST::codegenStr()
{
	switch (type)
	{
	case 0:
		return identifier->codegenStr();
	case 1:
		return left->identifier->codegenStr();
	default:
		break;
	}
	return NULL;
}

Value* VarNameAST::codegen()
{
	Value* expVal = nullptr;
	Value* LVarVal = nullptr;
	Value* RVarVal = nullptr;
	AllocaInst* allo = nullptr;
	Value* Val = nullptr;
	switch (type)
	{
	case 0:
		return NamedValues[identifier->codegenStr()];
	case 1://var_name[exp]
		expVal = exp->codegen();
		allo = NamedValues[this->codegenStr()];
		Val = Builder.CreateLoad(allo);




		return Val;
		//allo.
	case 2:

	case 3:

	case 4:

	default:
		break;
	}
	return nullptr;
}

Value* VarNameAST::expCodegen()
{
	if (this->exp != nullptr)
	{
		return exp->codegen();
	}
	return nullptr;
}