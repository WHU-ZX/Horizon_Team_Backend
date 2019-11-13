#include "StmtsAST.h"

StmtsAST::StmtsAST()
{
	this->stmtASTs = new vector<StmtAST*>();
}

StmtsAST::~StmtsAST()
{
	if (this->stmtASTs != nullptr)
	{
		for (int i = 0; i < this->stmtASTs->size(); i++)
		{
			delete this->stmtASTs->at(i);
		}
		delete this->stmtASTs;
	}
}

void StmtsAST::addStmtAST(StmtAST* ast)
{
	this->stmtASTs->push_back(ast);
}

Value* StmtsAST::codegen()
{
	//
	//FWH
	//

	Value* Val = nullptr;
	if (this->stmtASTs != nullptr)
	{
		for (int i = this->stmtASTs->size() - 1; i >= 0; i--)
		{
			Val = this->stmtASTs->at(i)->codegen();

			//���ĺ���11��12��23��41�޸�
			//������stmt��return����ôֱ�ӷ���
			if (this->stmtASTs->at(i)->son == 4) {
				return ConstantInt::get(IntegerType::get(TheContext, 32), APInt(32, 0));
			}

		}
	}

	return ConstantInt::get(IntegerType::get(TheContext, 32), APInt(32, 0));
	//return nullptr;


	//
	//LBQ
	//

	/*for (int i = this->stmtASTs->size() - 1; i >= 0; i--)
	{
		this->stmtASTs->at(i)->codegen();
	}
	return (Value*)stmtASTs;*/
}