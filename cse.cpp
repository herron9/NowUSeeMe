//
//  cse.cpp
//  project1
//
//  Created by RR on 4/18/16.
//  Copyright © 2016 rr. All rights reserved.
//

#include "cseMachine.h"
#include <iostream>
#include <string>
#include <map>
#include <cmath>

static cseNode* Genv =new envC(0,nullptr);
static vector<cseNode*> envV;
static bool printbool =false;
static cseNode* printnode;
static vector<cseNode*> printx;
static int concx=0;
static int countt=1;
static int envct=1;

void CSE::runCSE(TreeNode* root){
    //Initial
    cseNode* env = new envC(0,nullptr);
    Genv=env;
    CONTROL.push_back(env);
    envV.push_back(env);
    flatten(root);
    
    STACK.push_back(env);
    
    while (CONTROL.size()!=0) {
        
        cseNode* node =CONTROL.back();
        
        switch (node->cse_Type) {
            case 1:{//rule1
                cseNode* ob=lookup(node,dynamic_cast<envC*>(Genv));

                if(ob==nullptr) {
                    ISintrinsicFn(node);
                    STACK.push_back(node);
                }else{
                    STACK.push_back(ob);
                }
                CONTROL.pop_back();
                
                break;}
            case 7: {//rule2
                dynamic_cast<lambdaC*>(node)->env=dynamic_cast<envC*>(Genv);
                CONTROL.pop_back();
                STACK.push_back(node);
                break;
            }
            case 3:{//rule3->rule6 op
                cseNode* op=CONTROL.back();
                cseNode* rand1=STACK.back();
                STACK.pop_back();
                cseNode* rand2=STACK.back();
                STACK.pop_back();
                cseNode* result =binop(op, rand1, rand2);
                STACK.push_back(result);
                CONTROL.pop_back();//pop op
                break;
            }
            case 4:{//rule3->rule7 uop
                cseNode* op=CONTROL.back();
                cseNode* rand=STACK.back();
                STACK.pop_back();
                CONTROL.pop_back();
                cseNode* result =uop(op, rand);
                if (result==NULL) {
                    ;
                }else{
                    STACK.push_back(result);
                }
                
                break;
            }

            case 6:{
                cseNode* Snode =STACK.back();//rule11
                switch (Snode->cse_Type) {
                    case 7:{//rule4->rule11 n-ary function
                        int num=dynamic_cast<lambdaC*>(Snode)->variable.size();
                        STACK.pop_back();//pop lambda
                        cseNode * rand =STACK.back();
                        STACK.pop_back();//pop rand
//                        vector<cseNode*> rand;
//                        while (num>0) {
//                            cseNode* rad=STACK.back();
//                            rand.push_back(rad);
//                            STACK.pop_back();
//                            num--;
//                        }
                        cseNode* em= naryConvert(Snode, rand);
                        CONTROL.pop_back();
                        CONTROL.push_back(em);
                        TreeNode* idx=dynamic_cast<lambdaC*>(Snode)->index;
                        flatten(idx);
                        STACK.push_back(em);
                       break;
                    }
                    case 17:{//rule10 tuple selection
                        CONTROL.pop_back();
                        cseNode* tup =STACK.back();//get tuple
                        STACK.pop_back();
                        cseNode* I =STACK.back();//get index
                        int index = stoi(I->value.c_str());
                        STACK.pop_back();
                        cseNode* VI =dynamic_cast<tupleC*>(tup)->tuple[index-1];
                        STACK.push_back(VI);
                        break;
                    }
                    case 8:{//Ystar
                        CONTROL.pop_back();//pop G
                        STACK.pop_back();//pop Y
                        cseNode* temp = STACK.back();
                        TreeNode* ind=dynamic_cast<lambdaC*>(temp)->index;
                        cseNode* eta=new etaC(ETA,ind,dynamic_cast<envC*>(dynamic_cast<lambdaC*>(temp)->env));
                        dynamic_cast<etaC*>(eta)->vb=dynamic_cast<lambdaC*>(temp)->variable;
                        STACK.pop_back();//pop L
                        STACK.push_back(eta);
                        break;
                    }
                    case 9:{
                        cseNode* gc=new gammaC(GAMMa);
                        CONTROL.push_back(gc);
                        cseNode* temp =STACK.back();
                        TreeNode* ind=dynamic_cast<etaC*>(temp)->index;
                        cseNode* lc=new lambdaC(LAMBDa,ind);
                        dynamic_cast<lambdaC*>(lc)->env=dynamic_cast<envC*>(Genv);//?????????
//                        dynamic_cast<lambdaC*>(lc)->env=dynamic_cast<envC*>(dynamic_cast<etaC*>(temp)->env);
                        dynamic_cast<lambdaC*>(lc)->variable=dynamic_cast<etaC*>(temp)->vb;
                        STACK.push_back(lc);
                        break;
                    }
                    case 20://rpal
                    {
                        CONTROL.pop_back();//pop G
                        cseNode* ID =STACK.back();//get intriID
                        intrinsicFn(ID);
                        break;
                    }
                        
                }
                break;
            }
                
            case 13:{//rule5
                cseNode* emc=CONTROL.back();
                CONTROL.pop_back();
                cseNode* Snode =STACK.back();
                STACK.pop_back();
                cseNode* em =STACK.back();
                STACK.pop_back();//pop em
                if (dynamic_cast<envC*>(emc)->value!=dynamic_cast<envC*>(em)->value) {
                    cout<<"errorrrrrrrrr"<<endl;
                }
                STACK.push_back(Snode);
                int size=CONTROL.size();
                int i=size-1;
                while (i>=0&&CONTROL[i]->cse_Type!=ENV) {
                    i--;
                }
                if (i>=0) {
                    Genv=dynamic_cast<envC*>(CONTROL[i]);
//                    for (; i>=0; i--) {
//                        if (CONTROL[i]->cse_Type==ENV) {
//                            Genv=dynamic_cast<envC*>(CONTROL[i]);
//                        }
//                    }
                }
//                cout<<"xxxxxxxxx"<<i<<endl;

//                if(dynamic_cast<envC*>(em)->previous!=nullptr&&Snode->cse_Type!=LAMBDa&&Snode->cse_Type!=ETA)
//                    Genv=dynamic_cast<envC*>(em)->previous;
                break;
            }
            case 16:{//rule 9  tuple
                cseNode* tup= maketuple(node);
                CONTROL.pop_back();
                STACK.push_back(tup);
                break;
                
            }
            case 19:{//cond rule 8
                CONTROL.pop_back();//pop bate
                cseNode* cond=CONTROL.back();
                CONTROL.pop_back();//pop cond
                cseNode* TF=STACK.back();
                if(dynamic_cast<truthvalueC*>(TF)->value==true){
                    TreeNode* temp1=dynamic_cast<condC*>(cond)->then;
                    TreeNode* temp3=dynamic_cast<condC*>(cond)->then->getRS();
                    temp1->setRSnull();
                    flatten(temp1);
                    temp1->setRS(temp3);
                }else if(dynamic_cast<truthvalueC*>(TF)->value==false){
                    TreeNode* temp2=dynamic_cast<condC*>(cond)->elsE;
//                    TreeNode* temp3=dynamic_cast<condC*>(cond)->elsE->getRS();
                    temp2->setRSnull();
                    flatten(temp2);
//                    temp2->getRS()->setRS(temp3);
                }
                STACK.pop_back();
                break;
                
            }
            default: {
                cseNode* x=CONTROL.back();
                CONTROL.pop_back();
                STACK.push_back(x);
                break;
            }
        }//end switch
//        cout<<"---"<<countt<<"---"<<endl;
//        countt++;
//        cout<<"control----------------------                                                 ---------------------stack"<<endl;
//        print(CONTROL);
////        cout<<"------------stack"<<endl;
//        prints(STACK);
//        cout<<endl;
//        printenv(CONTROL);
//        printenvs(STACK);
//        cout<<endl;
    }
//    cout<<"the output is:"<<endl;
    if (printbool==true) {
        HasTAB(printnode);
    }else{
        cout<<" "<<endl;
    }
    
    
}

cseNode* CSE::lookup(cseNode* csen, envC* envc){
    string id=csen->value;
    map<string,cseNode*>::iterator iter;
    iter=envc->pairs.find(id);
    envC* temp=envc;
    while(temp->previous!=nullptr) {
        if(iter!=temp->pairs.end())
        {
            cseNode* re =iter->second;
            return re;
        }
        temp=temp->previous;
        iter=temp->pairs.find(id);
    }
    temp=envc;

    

    return nullptr;
}

cseNode* CSE::naryConvert(cseNode* lam, cseNode* rand){
    int num=dynamic_cast<lambdaC*>(lam)->variable.size();
    
    cseNode* em=new envC(envct,dynamic_cast<lambdaC*>(lam)->env);
    envct++;
    Genv=em;
    if (num==1) {
        string str= dynamic_cast<lambdaC*>(lam)->variable[0]->value;
        dynamic_cast<envC*>(em)->pairs.insert(pair<string, cseNode*>(str,rand));
    } else {
    while (num>0) {
        string str= dynamic_cast<lambdaC*>(lam)->variable[num-1]->value;
        cseNode* val=dynamic_cast<tupleC*>(rand)->tuple[num-1];
        dynamic_cast<envC*>(em)->pairs.insert(pair<string, cseNode*>(str,val));
        num--;
    }
    }
    return em;
}

cseNode* CSE::binop(cseNode* op, cseNode* rand1, cseNode* rand2){
    opC* opx= dynamic_cast<opC*>(op);
    int neflag=0;
    int eqflag=0;
    int a=0; int b=0;
    bool c=true; bool d=true;
    string e=""; string f="";
    if (rand1->cse_Type==INT&&rand2->cse_Type==INT) {
        a = stoi(rand1->value.c_str());
        b = stoi(rand2->value.c_str());
    }else if(rand1->cse_Type==TF&&rand2->cse_Type==TF)
    {
        c= dynamic_cast<truthvalueC*>(rand1)->value;
        d= dynamic_cast<truthvalueC*>(rand2)->value;
        
    }else if(rand1->cse_Type==STR&&rand2->cse_Type==STR){
        e=rand1->value;
        f=rand2->value;
        neflag=1;
        eqflag=1;
    }else if(rand1->cse_Type==NIL||rand1->cse_Type==TUPLE){
        
    }

    switch (opx->Tty) {
        case 300:{
            int x= a+b;
            cseNode* intc= new intC(INT,to_string(x));
            return intc;}
        case 301:{
            int y= a-b;
            cseNode* inc= new intC(INT,to_string(y));
            return inc;}
        case 302:{
            int y= a*b;
            cseNode* inc= new intC(INT,to_string(y));
            return inc;}
        case 310:{
            int y= a/b;
            cseNode* inc= new intC(INT,to_string(y));
            return inc;}
        case 303:{
            cseNode* thc;
            if (a<b) thc= new  truthvalueC(TF,true);
            else     thc= new  truthvalueC(TF,false);
            return thc;}
        case 304:{
            cseNode* thc;
            if (a<=b) thc= new  truthvalueC(TF,true);
            else     thc= new  truthvalueC(TF,false);
            return thc;}
        case 305:{
            cseNode* thc;
            if (a>b) thc= new  truthvalueC(TF,true);
            else     thc= new  truthvalueC(TF,false);
            return thc;}
        case 306:{
            cseNode* thc;
            if (a>=b) thc= new  truthvalueC(TF,true);
            else     thc= new  truthvalueC(TF,false);
            return thc;}
        case 307:{//&
            cseNode* thc;
            if (c&&d) thc= new  truthvalueC(TF,true);
            else     thc= new  truthvalueC(TF,false);
            return thc;}
        case 311:{//eq  int
            cseNode* thc;
            switch (eqflag) {
                case 0:
                {
                    if (a==b) thc= new  truthvalueC(TF,true);
                    else      thc= new  truthvalueC(TF,false);
                    return thc;
                }
                case 1:
                {
                    if (e.compare(f)==0) thc= new  truthvalueC(TF,true);
                    else      thc= new  truthvalueC(TF,false);
                    return thc;
                }
            }
            break;
        }
        case 312:{//ne  int
            cseNode* thc;
            switch (neflag) {
                case 0:
                {
                    if (a!=b) thc= new  truthvalueC(TF,true);
                    else      thc= new  truthvalueC(TF,false);
                    return thc;
                }
                case 1:
                {
                    if (e.compare(f)!=0) thc= new  truthvalueC(TF,true);
                    else      thc= new  truthvalueC(TF,false);
                    return thc;
                }
            }
            break;
        }
        case 605://or
        {
            cseNode* thc;
            if (c||d) thc= new  truthvalueC(TF,true);
            else      thc= new  truthvalueC(TF,false);
            return thc;
            
        }
        case 314://**
        {
            int y= pow(b,a);
            cseNode* inc= new intC(INT,to_string(y));
            return inc;
        }
        case 604:
        {
            if(rand1->cse_Type==NIL){
                cseNode* tp = new tupleC(1);
                dynamic_cast<tupleC*>(tp)->tuple.push_back(rand2);
                return tp;
            }
            if (rand1->cse_Type==TUPLE) {
                dynamic_cast<tupleC*>(rand1)->tuple.push_back(rand2);
                dynamic_cast<tupleC*>(rand1)->value=dynamic_cast<tupleC*>(rand1)->value+1;
                return rand1;

            }
            
            
        }
    }
    return NULL;
}

cseNode* CSE::uop(cseNode* op, cseNode* rand){
    UopC* opx= dynamic_cast<UopC*>(op);
    int a=0;
    bool c=true;
    if (rand->cse_Type==INT) {
        a = stoi(rand->value.c_str());
    }else if(rand->cse_Type==TF)
    {
        c= dynamic_cast<truthvalueC*>(rand)->value;
        
    }
        switch (opx->Tty) {
            case 606: {//not
                cseNode* tfc;
                if(c==true)  {tfc= new truthvalueC(TF,false); return tfc;}
                if(c==false) {tfc= new truthvalueC(TF,true);  return tfc;}
            }
            case  612:{
                int x= -a;
                cseNode* intc= new intC(INT,to_string(x));
                return intc;}
        }
    
    return NULL;
}

cseNode* CSE::maketuple(cseNode* tup){
    int num=dynamic_cast<tauC*>(tup)->value;
    cseNode* tupx =new tupleC(num);
//    vector<cseNode*> tuple(num-1);
    while (num>0) {
        cseNode* tu=STACK.back();
        dynamic_cast<tupleC*>(tupx)->tuple.push_back(tu);
//        tuple[num-1]=tu;
        STACK.pop_back();
        num--;
    }
    return  tupx;
}

void CSE::intrinsicFn(cseNode* node){
    if (node->value=="Print") {
        STACK.pop_back();//pop print
        printnode= STACK.back();
        printx.push_back(printnode);
        STACK.pop_back();
        cseNode* dummy = new dummyC();
        STACK.push_back(dummy);
        printbool=true;
    }
    if(node->value=="Stem"){
        STACK.pop_back();//pop stem
        string str= (STACK.back()->value).substr(0,1);
        STACK.pop_back();
        cseNode* node= new strC(STR,str);
        STACK.push_back(node);
        
    }
    if(node->value=="Isinteger"){
        STACK.pop_back();//pop op
        if(STACK.back()->cse_Type==INT){
            STACK.pop_back();
            cseNode* tf =new truthvalueC(TF,true);
            STACK.push_back(tf);
        } else if(STACK.back()->cse_Type!=INT){
            STACK.pop_back();
            cseNode* tf2 =new truthvalueC(TF,false);
            STACK.push_back(tf2);
        }
        
    }
    
    if(node->value=="Istruthvalue"){
        STACK.pop_back();//pop op
        if(STACK.back()->cse_Type==TF){
            STACK.pop_back();
            cseNode* tf =new truthvalueC(TF,true);
            STACK.push_back(tf);
        } else if(STACK.back()->cse_Type!=TF){
            STACK.pop_back();
            cseNode* tf2 =new truthvalueC(TF,false);
            STACK.push_back(tf2);
        }
        
    }
    if(node->value=="Isstring"){
        STACK.pop_back();//pop op
        if(STACK.back()->cse_Type==STR){
            STACK.pop_back();
            cseNode* tf =new truthvalueC(TF,true);
            STACK.push_back(tf);
        } else if(STACK.back()->cse_Type!=STR){
            STACK.pop_back();
            cseNode* tf2 =new truthvalueC(TF,false);
            STACK.push_back(tf2);
        }
        
    }
    if(node->value=="Istuple"){
        STACK.pop_back();//pop op
        if(STACK.back()->cse_Type==TUPLE||STACK.back()->cse_Type==NIL){
            STACK.pop_back();
            cseNode* tf =new truthvalueC(TF,true);
            STACK.push_back(tf);
        } else if(STACK.back()->cse_Type!=TUPLE){
            STACK.pop_back();
            cseNode* tf2 =new truthvalueC(TF,false);
            STACK.push_back(tf2);
        }
        
    }
    if(node->value=="Stern"){
        STACK.pop_back();//pop stern
        int length=(STACK.back()->value).length();
        string str= (STACK.back()->value).substr(1,length-1);
        STACK.pop_back();
        cseNode* node= new strC(STR,str);
        STACK.push_back(node);
        
    }
    if(node->value=="Conc"){
        STACK.pop_back();//pop conc
        string str1= STACK.back()->value;
        STACK.pop_back();
        string str2= STACK.back()->value;
        STACK.pop_back();
        string str=str1+str2;
        cseNode* node= new strC(STR,str);
        STACK.push_back(node);
        CONTROL.pop_back();//pop second G
        
    }
    if(node->value=="Order"){
        STACK.pop_back();//pop order
        cseNode* tmp=STACK.back();
        STACK.pop_back();//pop nil or tuple
        switch (tmp->cse_Type) {
            case 14://nil
            {
                cseNode* intc =new intC(INT,to_string(0));
                STACK.push_back(intc);
                break;}
            case 17:{
                int x= dynamic_cast<tupleC*>(tmp)->value;
                cseNode* intcx =new intC(INT,to_string(x));
                STACK.push_back(intcx);
                break;
            }
            default:  cout<<"error!!!!!!!!!!!!!!!"<<endl;
                break;
        }
    }
    
    if(node->value=="ItoS"){
        STACK.pop_back();//pop ItoS
        if (STACK.back()->cse_Type==INT) {
            string str= STACK.back()->value;
            STACK.pop_back();
            cseNode* node= new intC(INT,str);
            STACK.push_back(node);
        }else{
            cout<<"error!!!!!!!!!!!!!!!"<<endl;
        }
    }
    
}

void CSE::ISintrinsicFn(cseNode* node){
    if (node->value=="Print"||node->value=="Stem"||node->value=="Isinteger"||node->value=="Istruthvalue"||node->value=="Isstring"
        ||node->value=="Istuple"||node->value=="Stern"||node->value=="Conc"||node->value=="Order"||node->value=="ItoS") {
        node->cse_Type=RPAL;
//        cout<<node->value<<endl;
    }
}

void CSE::HasTAB(cseNode* node){
    if (printx.size()>1) {
        int cap=printx.size();
        for (int i=0; i<cap; i++) {
            cout<<printx[i]->value;
        }
        return;
    }
    if(node->cse_Type==STR){
    string str=node->value;
//    for(int i = 0; i < str.length(); i++) {
//        if (str[i]=='\\') {
//            if (str[i+1]=='n')  {cout<<endl;i=i+1;continue;}
//            if (str[i+1]=='t')  {cout<<"\t";i=i+1;continue;}
//            if (str[i+1]=='r')  {cout<<endl;i=i+1;continue;}
//        }else{
//            cout<<str[i];
//        }
//        
//    }
    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == '\\' && str.at(i + 1) == 'n') {
            cout << "\n";
            i++;
        } else if (str.at(i) == '\\' && str.at(i + 1) == 't') {
            cout << "\t";
            i++;
        } else {
            cout << str.at(i);
        }
    }
    }
    if (node->cse_Type==INT) {
        cout<<node->value<<endl;
    }
    if(node->cse_Type==TUPLE){
        int num=dynamic_cast<tupleC*>(node)->value;
        cout<<"(";
        for (int i=0; i<num-1; i++) {
            cout<<dynamic_cast<tupleC*>(node)->tuple[i]->value<<", ";
        }
        cout<<dynamic_cast<tupleC*>(node)->tuple[num-1]->value<<")"<<endl;
    }
    if(node->cse_Type==LAMBDa){
        cout<<"[lambda closure: x: 2]"<<endl;
    }
    if(node->cse_Type==TF){
        if(dynamic_cast<truthvalueC*>(node)->value==true) cout<<"true"<<endl;
        if(dynamic_cast<truthvalueC*>(node)->value==false) cout<<"false"<<endl;
        
    }
}
