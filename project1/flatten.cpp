//
//  flatten.cpp
//  project1
//
//  Created by RR on 4/18/16.
//  Copyright © 2016 rr. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "cseNode.h"
#include <string>
#include <iostream>


void TreeNode::flatten(){
    switch (TN_type) {
        case 1: {idC* idc= new idC;    idc->cse_Type=ID;   idc->value=TN_value; CONTROL.push(idc);break;}
        case 2: {intC* intc= new intC; intc->cse_Type=INT; intc->value=atoi(TN_value.c_str());CONTROL.push(intc);break;}
        case 3:   case 300: case 301: case 302: case 303: case 304: case 305:
        case 306: case 307: case 309: case 310: case 311: case 312: case 314:
        {opC* opc= new opC;    opc->cse_Type=OP;   opc->value=TN_value; CONTROL.push(opc);break;}
        case 606: case 612:
        {UopC* uopc =new UopC; uopc->cse_Type=UOP; uopc->value=TN_value;CONTROL.push(uopc);break;}
        case 4: {strC* strc= new strC; strc->cse_Type=STR; strc->value=TN_value;CONTROL.push(strc);break;}
        case 9: {gammaC* gc=new gammaC; gc->cse_Type=GAMMa; CONTROL.push(gc); break;}
        case 10:{
            lambdaC* lc=new lambdaC;
            lc->index=RightS;
            lc->cse_Type=LAMBDa;
            if (503==LeftC->TN_type) {
                TreeNode* temp =LeftC->LeftC;
                while (temp->RightS!=nullptr) {
                    idC* idc= new idC;
                    idc->cse_Type=ID;
                    idc->value=TN_value;
                    lc->variable.push_back(idc);
                    temp=temp->RightS;
                }
            }else
            {
                idC* idc= new idC;
                idc->cse_Type=ID;
                idc->value=TN_value;
                lc->variable.push_back(idc);
            }
            return;
        }
        case 11: {YstarC* yc =new YstarC;          yc->cse_Type=YStar; CONTROL.push(yc);break;}
        case 613:{truthvalueC* tc=new truthvalueC; tc->cse_Type=TRUTH;  tc->value=true; break;}
        case 614:{truthvalueC* fc=new truthvalueC; fc->cse_Type=FALSe;  fc->value=false; break;}
        case 506:{
            tauC* tauc =new tauC;
            tauc->cse_Type=TAU;
            TreeNode* temp= LeftC;
            tauc->value=0;
            while (temp->RightS!=nullptr) {
                tauc->value++;
                temp=temp->RightS;
            }
            CONTROL.push(tauc);
            temp=LeftC;
            while (temp!=nullptr)
            {
                temp->flatten();
                temp=temp->RightS;
            }
            return;
        }
        case 315:{
            condC* condc= new condC;
            condc->cse_Type=COND;
            condc->then=LeftC->RightS;
            condc->elsE=LeftC->RightS->RightS;
            CONTROL.push(condc);
            LeftC->flatten();
            return;
        }
        case 615:{nilC* nilc =new nilC; nilc->cse_Type=NIL; CONTROL.push(nilc);break;}
        default: {cout<<"errorrrrrrr!!!"<<endl; break;}
            
    }
    if (LeftC!= nullptr)
    {
        LeftC->flatten();
        if (LeftC->RightS!= nullptr)
        {
            LeftC->RightS->flatten();
        }
    }
    
}

void CtoS(stack<cseNode*> csestack){
    cseNode* temp;
    while (!csestack.empty()) {
        temp=csestack.top();
        STACK.push(temp);
        csestack.pop();
    }
}

void print(stack<cseNode*> csestack){
    while (!csestack.empty()) {
        cout<<csestack.top()->cse_Type<<" ";
        csestack.pop();
    }
}

