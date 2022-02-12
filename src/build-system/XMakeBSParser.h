//
// Created by maicss on 2022/2/12.
//

#ifndef DEPENDMANAGER_XMAKEBSPARSER_H
#define DEPENDMANAGER_XMAKEBSPARSER_H

#include "BSParser.h"

class XMakeBSParser : public BSParser{
public:
    bool isValid();
    bool getDepends(DependList &dependList);
};


#endif //DEPENDMANAGER_XMAKEBSPARSER_H
