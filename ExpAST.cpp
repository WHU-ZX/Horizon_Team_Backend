#include "ExpAST.h"
#include "VarNameAST.h"

ExpAST::ExpAST(ExpAST* left, OperatorAST* operatorAST)//��Ŀ
{
	this->left = left;
	this->operatorAST= operatorAST;
	this->type = 0;
}

ExpAST::ExpAST(ExpAST* left, ExpAST* right, OperatorAST* operatorAST)//˫Ŀ
{
	this->left = left;
	this->right = right;
	this->operatorAST = operatorAST;
	this->type = 1;
}

void ExpAST::setStructName(string name)
{
	this->structName = name;
}

ExpAST::ExpAST(ValAST* valAST)//<val>
{
	this->valAST = valAST;
	this->type = 2;
}

ExpAST::ExpAST(VarNameAST* varNameAST)//<var_name>
{
	this->varNameAST = varNameAST;
	this->type = 3;
}

ExpAST::ExpAST(FuncCallStmtAST* funcCallStmtAST)
{
	this->funcCallStmtAST = funcCallStmtAST;
	this->type = 4;
}

void ExpAST::setType(zx::Type expType)
{
	this->expType = expType;
}

void ExpAST::setFinalToType(zx::Type type)
{
	this->finalToType = type;
}

void ExpAST::setPointerNum(int num)
{
	this->pointerNum = num;
}

ExpAST::~ExpAST()
{
	if (this->left != nullptr)
	{
		this->left = left;
	}
	if (this->right != nullptr)
	{
		this->right = right;
	}
	if (this->valAST != nullptr)
	{
		this->valAST = valAST;
	}
	if (this->varNameAST != nullptr)
	{
		this->varNameAST = varNameAST;
	}
	if (this->operatorAST != nullptr)
	{
		delete this->operatorAST;
	}
	if (this->funcCallStmtAST != nullptr)
	{
		delete this->funcCallStmtAST;
	}
}

Value* ExpAST::codegen() {
	Value* LVar = nullptr;
	Value* RVar = nullptr;
	Value* Val = nullptr;
	AllocaInst* allo = nullptr;
	ConstantFP* LVarV = nullptr;
	bool BothIsInterger;
	if (left != NULL) {
		LVar = left->codegen();
	}
	if (right != NULL) {
		RVar = right->codegen();
	}
	switch (type)
	{
	case 0:
		switch (operatorAST->op)
		{
		case Op::NOT:
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			Val = Builder.CreateNot(LVar);
			//Val->getType()->print(errs());  //i32
			//cout << endl;
			Val->print(errs());
			std::cout << "\n";
			return Val;
		case Op::MINUS:
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			Val = Builder.CreateNeg(LVar);
			//Val->getType()->print(errs()); //i32
			//cout << endl;
			Val->print(errs());
			std::cout << "\n";
			return Val;
		case Op::STAR:
			/*Val = Builder.CreateNot(LVar, "Not tmp");
			Val->print(errs());
			std::cout << "\n";
			return Val;*/
			break;
		}
		break;
	case 1://˫Ŀ�����
		switch (operatorAST->op)
		{
		case Op::ADD:
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			if (AllocaInst::classof(RVar) || GlobalVariable::classof(RVar)) {
				RVar = Builder.CreateLoad(RVar);
			}
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				Val = Builder.CreateAdd(LVar, RVar);
				//Val->print(errs());
				//std::cout << "\n";
				return Val;
			}
			//�����ƺ����ü��ж�Ҳ����������IR����
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}
			Val = Builder.CreateFAdd(LVar, RVar);
			Val->print(errs());
			std::cout << "\n";
			return Val;
		case Op::MINUS:
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			if (AllocaInst::classof(RVar) || GlobalVariable::classof(RVar)) {
				RVar = Builder.CreateLoad(RVar);
			}
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				Val = Builder.CreateSub(LVar, RVar);
				//Val->print(errs());
				//cout << "\n";
				return Val;
			}
			//�����ƺ����ü��ж�Ҳ����������IR����
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}
			Val = Builder.CreateFSub(LVar, RVar);
			Val->print(errs());
			cout << "\n";
			return Val;
		case Op::STAR:
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			if (AllocaInst::classof(RVar) || GlobalVariable::classof(RVar)) {
				RVar = Builder.CreateLoad(RVar);
			}
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				Val = Builder.CreateMul(LVar, RVar);
				//Val->print(errs());
				//cout << "\n";
				return Val;
			}
			//�����ƺ����ü��ж�Ҳ����������IR����
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}


			//���ڳ˷��ͳ�����Val�����errs()��ʱ����ʮ����������16λ16������
			//��IEEE��������׼���㣨��ϵͳ�����������д�ķ����������������16����������������ȷ���
			//���廻���Ѿ�д����IEEEConvert��Ŀ
			Val = Builder.CreateFMul(LVar, RVar, "multmp");
			Val->print(errs());
			cout << "\n";
			return Val;
		case Op::DIVIDE://�����������int���ͣ�ҲҪת����
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			if (AllocaInst::classof(RVar) || GlobalVariable::classof(RVar)) {
				RVar = Builder.CreateLoad(RVar);
			}
			BothIsInterger = true;
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				Val = Builder.CreateSDiv(LVar, RVar);
				//Val->print(errs());
				//cout << "\n";
				return Val;
			}

			//�����ƺ����ü��ж�Ҳ����������IR����
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}

			Val = Builder.CreateFDiv(LVar, RVar);
			Val->print(errs());
			cout << "\n";

			//���ڳ˷��ͳ�����Val�����errs()��ʱ����ʮ����������16λ16������
			//��IEEE��������׼���㣨��ϵͳ�����������д�ķ����������������16����������������ȷ���
			//���廻���Ѿ�д����IEEEConvert��Ŀ
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				Val = Builder.CreateFPToSI(Val, IntegerType::get(TheContext, 32));
				Val->print(errs());
				cout << "\n";
			}
			return Val;
		case Op::MORE:
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			if (AllocaInst::classof(RVar) || GlobalVariable::classof(RVar)) {
				RVar = Builder.CreateLoad(RVar);
			}
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				Val = Builder.CreateICmpSGT(LVar, RVar, "GreaterTmp");
				Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
				//Val->print(errs());
				//cout << "\n";
				return Val;
			}
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}
			Val = Builder.CreateICmpSGT(LVar, RVar);
			Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
			Val->print(errs());
			cout << "\n";
			return Val;
		case Op::MOREOREQ:
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			if (AllocaInst::classof(RVar) || GlobalVariable::classof(RVar)) {
				RVar = Builder.CreateLoad(RVar);
			}
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				//Val = Builder.CreateMul(LVar, RVar);
				Val = Builder.CreateICmpSGE(LVar, RVar);
				Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
				//Val->print(errs());
				//cout << "\n";
				return Val;
			}
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}
			Val = Builder.CreateFCmpOGE(LVar, RVar);
			Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
			return Val;
		case Op::LESS:
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			if (AllocaInst::classof(RVar) || GlobalVariable::classof(RVar)) {
				RVar = Builder.CreateLoad(RVar);
			}
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				//Val = Builder.CreateMul(LVar, RVar);
				Val = Builder.CreateICmpSLT(LVar, RVar);
				Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
				//Val->print(errs());
				//cout << "\n";
				return Val;
			}
			LVar->getType()->print(errs());
			cout << endl;
			RVar->getType()->print(errs());
			cout << endl;
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}
			Val = Builder.CreateFCmpOLT(LVar, RVar);
			Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
			return Val;
		case Op::LESSOREQ:
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			if (AllocaInst::classof(RVar) || GlobalVariable::classof(RVar)) {
				RVar = Builder.CreateLoad(RVar);
			}
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				//Val = Builder.CreateMul(LVar, RVar);
				Val = Builder.CreateICmpSLE(LVar, RVar);
				Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
				//Val->print(errs());
				//cout << "\n";
				return Val;
			}
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}
			Val = Builder.CreateFCmpOLE(LVar, RVar);
			Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
			return Val;
		case Op::EQ:
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			if (AllocaInst::classof(RVar) || GlobalVariable::classof(RVar)) {
				RVar = Builder.CreateLoad(RVar);
			}
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				//Val = Builder.CreateMul(LVar, RVar);
				Val = Builder.CreateICmpEQ(LVar, RVar);
				Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
				//Val->print(errs());
				//cout << "\n";
				return Val;
			}
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}
			Val = Builder.CreateFCmpOEQ(LVar, RVar);
			Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
			return Val;
		case Op::NEQ:
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			if (AllocaInst::classof(RVar) || GlobalVariable::classof(RVar)) {
				RVar = Builder.CreateLoad(RVar);
			}
			if (IntegerType::classof(LVar->getType()) && IntegerType::classof(RVar->getType())) {
				//���Լ��ϵ�����������ΪIR����е���ʱ������
				//Val = Builder.CreateMul(LVar, RVar);
				Val = Builder.CreateICmpNE(LVar, RVar);
				Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
				//Val->print(errs());
				//cout << "\n";
				return Val;
			}
			if (IntegerType::classof(LVar->getType())) {
				LVar = Builder.CreateSIToFP(LVar, Type::getDoubleTy(TheContext));
				LVar->print(errs());
				cout << "\n";
			}
			if (IntegerType::classof(RVar->getType())) {
				RVar = Builder.CreateSIToFP(RVar, Type::getDoubleTy(TheContext));
				RVar->print(errs());
				cout << "\n";
			}
			Val = Builder.CreateFCmpONE(LVar, RVar);
			Val = Builder.CreateZExt(Val, IntegerType::get(TheContext, 32));
			return Val;
		case Op::AND://CreateAnd�ѵ��ǰ�λ����
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			if (AllocaInst::classof(RVar) || GlobalVariable::classof(RVar)) {
				RVar = Builder.CreateLoad(RVar);
			}
			Val = Builder.CreateAnd(LVar, RVar);
			//cout << endl;
			//Val->getType()->print(errs());//    Val->getType() == i32 (1λ�޷�������)
			Val->print(errs());
			cout << "\n";
			return Val;
		case Op::OR:
			if (AllocaInst::classof(LVar) || GlobalVariable::classof(LVar)) {
				LVar = Builder.CreateLoad(LVar);
			}
			if (AllocaInst::classof(RVar) || GlobalVariable::classof(RVar)) {
				RVar = Builder.CreateLoad(RVar);
			}
			Val = Builder.CreateOr(LVar, RVar);
			//Val->print(errs());
			//cout << "\n";
			return Val;
		default:
			break;
		}
		break;
	case 2://Val
		return valAST->codegen();
	case 3://varName
		/*return NamedValues[varNameAST->codegenStr()];*/
		if (varNameAST->type == 1) {//����������ĳ��Ԫ�� --> ��ô�ͷ���һ��AllocaInst* �� ��Ҫ�޸������case1����
			/*allo = NamedValues[varNameAST->codegenStr()];
			Val = Builder.CreateLoad(allo);*/
			Val = varNameAST->codegen();

			if (ArrayType::classof(Val->getType())) {

			}
			else {//wrong

			}
			Val->print(errs());
		}
		else if(varNameAST->type == 0){//varName->identifier  �Ƿ�ҲӦ�÷���AllocaInst* ��
			//allo = NamedValues[varNameAST->codegenStr()];
			allo = getHighestValue(varNameAST->codegenStr());
			if (allo == nullptr) {//���β�����
				//currentFun->arg
			}
			//Val = Builder.CreateLoad(allo);


			//return Val;
			return allo;
		}
		else if (varNameAST->type == 4) {// varName -> * exp   , �����������

		}
		


		if (Val->getType()->isArrayTy()) {
			if (Val->getType()->getArrayElementType()->isIntegerTy()) {//int[]
				cout << 1;
			}
			else if (Val->getType()->getArrayElementType()->isDoubleTy()) {//real[]
				cout << 2;
			}
			//else if()
		}

		Val->print(errs());
		cout << "\n";
		return Val;
	case 4:
		return this->funcCallStmtAST->codegen();
	default:
		break;
	}
	return nullptr;
}

string ExpAST::codegenStr() {
	switch (type)
	{
	case 3:
		return varNameAST->codegenStr();

	default:
		break;
	}
}