//
//  flatten.cpp
//  project1
//
//  Created by RR on 4/18/16.
//  Copyright © 2016 rr. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "cseMachine.h"
#include <string>
#include <iostream>
#include <vector>


void CSE::flatten(TreeNode* node){
    switch (node->getIntType()) {
        case 1: {cseNode* idc=new idC(ID, node->getStrValue());     CONTROL.push_back(idc);break; }
        case 2: {cseNode* intc= new intC(INT,node->getStrValue()); CONTROL.push_back(intc);break;}
        case 3:   case 300: case 301: case 302: case 303: case 304: case 305:
        case 306: case 307: case 309: case 310: case 311: case 312: case 314: case 605: case 604:
                {cseNode* opc= new opC(OP,node->getIntType(),node->getStrValue());     CONTROL.push_back(opc);break;}
        case 606: case 612:
                {cseNode* uopc =new UopC(UOP,node->getIntType(),node->getStrValue()); CONTROL.push_back(uopc);break;}
        case 4: {cseNode* strc= new strC(STR,node->getStrValue()); CONTROL.push_back(strc);break;}
        case 9: {cseNode* gc=new gammaC(GAMMa);                  CONTROL.push_back(gc); break;}
        case 10:{
            cseNode* lc=new lambdaC(LAMBDa,node->getLC()->getRS());
            if (503==node->getLC()->getIntType()) {
                TreeNode* temp =node->getLC()->getLC();
                while (temp!=nullptr) {
                    cseNode* idc= new idC(ID,temp->getStrValue());
                    (dynamic_cast<lambdaC*>(lc))->variable.push_back(idc);
                    temp=temp->getRS();
                }
            }else
            {
                cseNode* idc= new idC(ID,node->getLC()->getStrValue());
                 (dynamic_cast<lambdaC*>(lc))->variable.push_back(idc);
            }
            CONTROL.push_back(lc);
            if(node->getRS()!=nullptr&&node->getRS()!=NULL) flatten(node->getRS());
            return;
        }
        case 11: {cseNode* yc =new YstarC(); CONTROL.push_back(yc);break;}
        case 613:{cseNode* tc=new truthvalueC(TF,true);  CONTROL.push_back(tc);break;}
        case 614:{cseNode* fc=new truthvalueC(TF,false); CONTROL.push_back(fc);break;}
        case 506:{
            TreeNode* temp= node->getLC();
            int c=1;
            while (temp->getRS()!=nullptr) {
                c++;
                temp=temp->getRS();
            }
            cseNode* tauc =new tauC(TAU,c);
            CONTROL.push_back(tauc);
            
            temp=node->getLC();
            if (temp!=nullptr)
            {
                flatten(temp);
            }
            TreeNode* temp3=node->getRS();
            if (temp3!=nullptr)
            {
                flatten(temp3);
            }
            return;
        }
        case 315:{//->
            cseNode* condc= new condC(COND,node->getLC()->getRS(),nullptr);
            if (node->getLC()->getRS()->getRS()!=nullptr) {
                dynamic_cast<condC*>(condc)->elsE=node->getLC()->getRS()->getRS();
            }else{
                dynamic_cast<condC*>(condc)->elsE=node->getLC()->getRS();
            }
            CONTROL.push_back(condc);
            cseNode* opc=new bataC(BATA);
            CONTROL.push_back(opc);
            TreeNode* temp=node->getLC();
            TreeNode* temp2=node->getLC()->getRS();
            temp->setRSnull();
            flatten(temp);
            node->getLC()->setRS(temp2);
            return;
        }
        case 615:{cseNode* nilc =new nilC(NIL); CONTROL.push_back(nilc);break;}
        case 616:{cseNode* dummyc =new dummyC(); CONTROL.push_back(dummyc);break;}
        case 8:{cseNode* yc =new YstarC(); CONTROL.push_back(yc);break;}//ystar
        default: {cout<<"error!!!"<<endl;break;}
            
    }
    if (node->getLC()!= nullptr)
    {
        flatten(node->getLC());}
    
    if (node->getRS()!= nullptr)
    {
        flatten(node->getRS());
    }

    
}


void CSE::print(const vector<cseNode*> valList)
{
    int count = valList.size();
    for (int i = 0; i < count;i++)
    {
        CseType x=static_cast<CseType>(valList[i]->cse_Type);
        if (x==ENV) {
            cout <<x<<"("<<dynamic_cast<envC*>(valList[i])->value<<")|";
        }else{
            cout <<x<<" "<<valList[i]->value<<"|";
        }
        
    }
    cout<<"      ";
}

void CSE::prints(const vector<cseNode*> valList)
{
    int count = valList.size();
    for (int i = count-1; i >=0;i--)
    {
        CseType x=static_cast<CseType>(valList[i]->cse_Type);
        if (x==ENV) {
            cout <<x<<"("<<dynamic_cast<envC*>(valList[i])->value<<")|";
        }else{
            cout <<x<<" "<<valList[i]->value<<"|";
        }
    }
    cout<<"      ";
}

void CSE::printenv(const vector<cseNode*> valList)
{
    cout<<endl;
    int count = valList.size();
//    map<string,cseNode*> words;

    for (int i = 0; i < count;i++)
    {
        CseType x=static_cast<CseType>(valList[i]->cse_Type);
        if (x==13) {
            map<string,cseNode*>::iterator it=dynamic_cast<envC*>(valList[i])->pairs.begin();
            int num= dynamic_cast<envC*>(valList[i])->value;
            cout<<"e"<<num<<"=";
            for (;it!=dynamic_cast<envC*>(valList[i])->pairs.end();++it) {
                cout<<it->first<<" "<<it->second->cse_Type<<","<<it->second->value<<"|";
            }
            if (dynamic_cast<envC*>(valList[i])->previous!=nullptr) {
                cout <<"pre:e("<<dynamic_cast<envC*>(dynamic_cast<envC*>(valList[i])->previous)->value <<")";
            }
            
            cout<<";";
        }
        
    }
//    cout<<"      ";
}

void CSE::printenvs(const vector<cseNode*> valList)
{
    cout<<endl;
    int count = valList.size();
    //    map<string,cseNode*> words;
    
    for (int i = count-1; i >=0;i--)
    {
        CseType x=static_cast<CseType>(valList[i]->cse_Type);
        if (x==13) {
            map<string,cseNode*>::iterator it=dynamic_cast<envC*>(valList[i])->pairs.begin();
            int num= dynamic_cast<envC*>(valList[i])->value;
            cout<<"e"<<num<<"=";
            for (;it!=dynamic_cast<envC*>(valList[i])->pairs.end();++it) {
                cout<<it->first<<" "<<it->second->cse_Type<<","<<it->second->value<<"|";
            }
            if (dynamic_cast<envC*>(valList[i])->previous!=nullptr) {
                cout <<"pre:e("<<dynamic_cast<envC*>(dynamic_cast<envC*>(valList[i])->previous)->value <<")";
            }
            cout<<";";
        }
        
    }
}