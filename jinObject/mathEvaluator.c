#include "mathEvaluator.h"
double getNumber(char* s);
double compute(char* expression);
enum{
    ISNUMBER,
    ISLETTER,
    ISPARENT
};

#define isnumber(x) isdigit(x)

static char* pi = "3.1415926535897932384626433832795028841971693993751058";

static const char operator[] = {'+','-','*','/','^'};

static const int numberOfOperator = sizeof(operator);
static const char parentheses[] = {'(',')'};

static bool isOverFlowed = false;


static char* func[]={"sin","cos","tan","sqrt","exp","ln","log2","log10","degree","radians","atan"};
int funCount = sizeof(func)/sizeof(char*);

static stack* numberStack = NULL;
static stack* operatorStack = NULL;
int inLevel = -1;


bool isParen(char* ch){
    if (ch[0] == parentheses[0] || ch[0] == parentheses[1]) {
        return true;
    }
    return false;
}

bool isFunc(char* ch){
    char* temp;
    if (!isalpha(ch[0])) {
        return false;
    }
    for (int i = 0; i<funCount; i++) {
        temp = strstr(ch, func[i]);
        if (temp) {
            return true;
        }
    }
    return false;
}

bool isInfinity(char* ch){
    if (strstr(ch, "inf")) {
        return true;
    }
    return false;
}

bool isNum(char* ch){
    return isnumber(ch[0]);
}

bool inOperatorSet(char ch){
    for (int i =0; i<numberOfOperator; i++) {
        if (operator[i]==ch) {
            return true;
        }
    }
    return false;
}

int determinType(char ch){
    if (isnumber(ch) || ch == '.') {
        return ISNUMBER;
    }
    if (isalpha(ch)) {
        return ISLETTER;
    }
    if (ch == parentheses[0] || ch == parentheses[1]) {
        return ISPARENT;
    }
    return -1;
}



void deleteMathString(MathString* obj){
    free(obj->object);
    free(obj);
}

void printMathString(MathString *obj){
    printf("left: %g\n",obj->left);
    printf("right: %g\n",obj->right);
    printf("string: %g\n",obj->string);
    printf("operString: %c\n",obj->operString);
    printf("Numbers are: ");
    printf("Number of Nums to Operator: %d\n",obj->numberOfNumsPointToOperator);
    printf("Index: %d\n",obj->index);
    printf("\n");
}

void deleteMathStringInStack(void* obj){
    deleteJinObject(*(MathString**)obj);
}
void printMathStringInStack(void* obj){
    printMathString(*(MathString**)obj);
}

MathString* initMathString(){
    MathString* temp = cnew(MathString);
    if (temp==NULL){
        printf("Cannot allocate MathString, do not have enough memory.\n");
        return NULL;
    }
    temp->object = initJObject();
    temp->object->className="MathString";
    temp->object->selfPointer=temp;
    temp->object->superClassIsJObject = true;
    temp->object->objectSize=sizeof(MathString);
    temp->object->dealloc = deleteMathString;
    temp->object->print = printMathString;
    temp->left = NAN;
    temp->right = NAN;
    temp->string = NAN;
    temp->numberOfNumsPointToOperator = 0;
    temp->index=-1;
    temp->operString = 0;
    return temp;
}


void increaseLevel(){
    inLevel++;
    if (!numberStack) {
        numberStack = initStack(sizeof(stack*),NULL);
    }
    if (!operatorStack) {
        operatorStack = initStack(sizeof(stack*), NULL);
    }
    stack* num = initStack(sizeof(MathString*), deleteMathStringInStack);
    num->print= printMathStringInStack;
    stack* oper = initStack(sizeof(MathString*), deleteMathStringInStack);
    oper->print= printMathStringInStack;
    pushStackAtIndex(&num, inLevel, numberStack);
    pushStackAtIndex(&oper, inLevel, operatorStack);
}

stack* getNumStack(){
    stack* temp;
    getStackValueAtIndex(&temp, inLevel, numberStack);
    return temp;
}

stack* getOperStack(){
    stack* temp;
    getStackValueAtIndex(&temp, inLevel, operatorStack);
    return temp;
}

void decreaseLevel(){
    stack* temp;
    popStackAtIndex(&temp, inLevel, numberStack);
    freeStack(temp);
    popStackAtIndex(&temp, inLevel, operatorStack);
    freeStack(temp);
    inLevel--;
    if (inLevel == -1) {
        freeStack(numberStack);
        freeStack(operatorStack);
        numberStack = NULL;
        operatorStack = NULL;
    }
}

int getOperatorPriority(char oper){
    switch (oper) {
        case '+':
            return 1;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 4;
        case '^':
            return 5;
        default:
            printf("'%c' is not an operator.\n",oper);
            return 0;
    }
}

int compareOperatorPriority(char l,char r){
    return getOperatorPriority(l)-getOperatorPriority(r);
}

char* replaceMinus(char* expression){
    char* expr = replaceStr(expression, "+-", "-");
    expression = replaceStr(expr, "--", "+");
    free(expr);
    expr = replaceStr(expression, "*-", "*-1*");
    free(expression);
    expression = replaceStr(expr, "/-", "*-1/");
    free(expr);
    return expression;
}



void setUpArrays(char* expression){
    if (expression == NULL) {return;}
    int t;
    char ch;
    bool inParent = false;
    bool inFunc = false;
    int parentCount = 0;
    double tempS;
    vector* v = charVector();
    stack* numArray = getNumStack();
    stack* operArray = getOperStack();
    MathString* numS;
    MathString* operS;
    char lastOper;
    for (int i = 0,len =(int)strlen(expression); i< len;i++) {
        ch = expression[i];
        t = determinType(ch);
        if (t == ISNUMBER) {
            if (v->currentSize!=0 && getCharValueFromIndex((int)v->currentSize-1, v)=='e') {
                inFunc = false;
            }
            pushToVector(ch, v);
        }
        else if (t == ISLETTER){
            inFunc = true;
            pushToVector(ch, v);
        }
        else if (t == ISPARENT){
            inParent = true;
            if (ch == parentheses[0]){parentCount++;}
            else if (ch == parentheses[1]){parentCount--;}
            if (parentCount==0) {
                inParent=false;
                if (inFunc) {
                    inFunc = false;
                }
            }
            pushToVector(ch, v);
        }
        else if(inOperatorSet(ch)){
            if (inParent) {
                pushToVector(ch, v);
                continue;
            }
            if (ch=='-' && v->currentSize!=0 && getCharValueFromIndex((int)v->currentSize-1, v)=='e') {
                inFunc = false;
                pushToVector(ch, v);
                continue;
            }
            if (ch == '-' && (lastOper == '*' || lastOper == '/' || lastOper == '^') && v->currentSize==0) {
                pushToVector(ch, v);
                continue;
            }
            pushToVector('\0', v);
            tempS = getNumber(v->value);
            freeVector(v);
            v = charVector();
            numS = initMathString();
            operS = initMathString();
            numS->string = tempS;
            numS->index = (int)numArray->length;
            operS->operString = ch;
            pushStack(&numS, numArray);
            pushStack(&operS, operArray);
            lastOper = ch;
        }
        else{
            printf("error in inputs.\n");
        }
    }
    numS= initMathString();
    pushToVector('\0', v);
    tempS = getNumber(v->value);
    freeVector(v);
    numS->string = tempS;
    numS->index = (int)numArray->length;
    pushStack(&numS, numArray);
}

void connectNumberAndOperator(){
    stack* numArray = getNumStack();
    stack* operArray = getOperStack();
    if (numArray->length <=1) {
        return;
    }
    MathString* s;
    for (int i =0; i < operArray->length; i++) {
        getStackValueAtIndex(&s, i, operArray);
        s->left = NAN;
        s->right = NAN;
        s->numberOfNumsPointToOperator = 0;
    }
    MathString *first;
    MathString *oper;
    MathString* operPrev;
    long len = operArray->length;
    int i =0;
    for (; i<len; i++) {
        getStackValueAtIndex(&first, i, numArray);
        first->index = i;
        if (i==0) {
            getStackValueAtIndex(&oper, i, operArray);
            oper->left = first->string;
            if (oper->index < 0) {
                oper->index = first->index;
            }
            else{
                oper->index = (oper->index < first->index)? oper->index:first->index;
            }
            oper->numberOfNumsPointToOperator++;
            continue;
        }
        getStackValueAtIndex(&oper, i, operArray);
        getStackValueAtIndex(&operPrev, i-1, operArray);
        if (compareOperatorPriority(oper->operString, operPrev->operString) > 0) {
            oper->left = first->string;
            if (oper->index<0) {
                oper->index = first->index;
            }
            else{
                oper->index = (oper->index < first->index) ? oper->index:first->index;
            }
            oper->numberOfNumsPointToOperator++;
        }
        else{
            operPrev->right = first->string;
            if (operPrev->index < 0) {
                operPrev->index = first->index;
            }
            else{
                operPrev->index = (operPrev->index < first->index)? operPrev->index:first->index;
            }
            operPrev->numberOfNumsPointToOperator++;
        }
    }
    getStackValueAtIndex(&first, i, numArray);
    getStackValueAtIndex(&oper, i-1, operArray);
    if (isnan(oper->left)) {
        oper->left = first->string;
    }
    else{
        oper->right = first->string;
    }
    if (oper->index<0) {
        oper->index = first->index;
    }
    else{
        oper->index = (oper->index < first->index) ? oper->index:first->index;
    }
    oper->numberOfNumsPointToOperator++;
    
}

char* dePrand(char* expression){
    if (expression==NULL) {
        return NULL;
    }
    char* start = strstr(expression, "(");
    cRaise(start==NULL, "error function inputs.");
    start++;
    size_t len = strlen(start);
    int count=1;
    int i =0;
    for (; i<len; i++) {
        if (start[i]=='(') {
            count++;
        }
        else if (start[i]==')'){
            count--;
        }
        if (count==0) {
            break;
        }
    }
    char* end = start+i;
    char* result = malloc(end-start+1);
    if (result == NULL) {
        printf("memory allocation failed in dePrand.\n");
        return NULL;
    }
    memset(result, '\0', end-start+1);
    strncpy(result, start, end-start);
    //return string allocated from heap, should be deallocated after use*/

    return result;
}

double evalFunc(char* expression, double num){
    size_t count = strlen(expression);
    vector *v = charVector();
    for (int i =0; i<count; i++) {
        if (expression[i]=='(') {
            break;
        }
        else{
            pushToVector(expression[i],v);
        }
    }
    pushToVector('\0', v);
    char* fun = ((char*)v->value)[0]!='-'? (char*)v->value:((char*)v->value)+1;
    double result;
    if (strcmp(fun, "sin")==0) {
        result= sin(num);
    }
    else if (strcmp(fun, "cos")==0) {
        result= cos(num);
    }
    else if (strcmp(fun, "tan")==0) {
        result= tan(num);
    }
    else if (strcmp(fun,"sqrt")==0)
    {
        result = sqrt(num);
    }
    else if (strcmp(fun,"exp")==0)
    {
        result = exp(num);
    }
    else if (strcmp(fun,"ln")==0)
    {
        result = log(num);
    }
    else if (strcmp(fun,"log2")==0)
    {
        result = log2(num);
    }
    else if (strcmp(fun,"log10")==0)
    {
        result = log10(num);
    }
    else if (strcmp(fun,"degree")==0)
    {
        result = degree(num);
    }
    else if (strcmp(fun,"radians")==0)
    {
        result = radians(num);
    }
    else if (strcmp(fun,"atan")==0)
    {
        result = atan(num);
    }
    else{
        printf("no function match, return 0.\n");
        result = 0;
    }
    result = ((char*)v->value)[0]!='-'? result:result*-1;
    freeVector(v);
    if (result == INFINITY || result== -INFINITY) {
        printf("calculation overflows, infinite number.\n");
        isOverFlowed =true;
    }
    return result;
}


double getNumber(char* s){
    double result;
    if (isNum(s) || (s[0]=='-' && isNum(s+1)) || isInfinity(s)) {
        sscanf(s, "%lf",&result);
        return result;
    }
    else if (isFunc(s[0]!='-'? s:s+1)){
        char* dep =dePrand(s);
        result = compute(dep);
        free(dep);
        result = evalFunc(s, result);
        return result;
    }
    else if (isParen(s)){
        char* dep = dePrand(s);
        result = compute(dep);
        free(dep);
        return result;
    }
    else{
        return 0;
    }
}

MathString* calculate(MathString* s){
    double l = s->left;
    double r = s->right;
    double result;
    switch (s->operString) {
        case '+':
            result = l+r;
            break;
        case '-':
            result = l-r;
            break;
        case '*':
            result = l*r;
            break;
        case '/':
            if (r == 0) {
                printf("divide by zero.\n");
                isOverFlowed = true;
            }
            result = l/r;
            break;
        case '^':
            result = pow(l, r);
            break;
        default:
            result = INFINITY;
            break;
    }
    if (result == INFINITY || result== -INFINITY) {
        printf("calculation overflows, infinite number.\n");
        isOverFlowed =true;
    }
    MathString *temp = initMathString();

    temp->string =result;
    temp->index = s->index;
    return temp;
}



bool PrandNotEqual(char* expression){
    int left = 0;
    int right = 0;
    size_t count = strlen(expression);
    for (int i =0; i<count; i++) {
        if (expression[i]=='(') {
            left++;
        }
        else if(expression[i]==')'){
            right++;
        }
    }
    return left!=right;
}



double compute(char* expression){
    increaseLevel();
    double result = 0;
    expression = replaceMinus(expression);
    setUpArrays(expression);
    stack* numArray = getNumStack();
    stack* operArray = getOperStack();
    MathString* temp;
    free(expression);
    if (numArray->length == 1 && operArray->length == 0) {
        getStackValueAtIndex(&temp, 0, numArray);
        result = temp->string;
        decreaseLevel();
        return result;
    }
    else if (numArray->length >1 && operArray->length == 0){
        printf("error in inputs.\n");
        decreaseLevel();
        return 0;
    }
    else{
        connectNumberAndOperator();
    }
    //printStack(operArray);
    //printf("------------------------------------------\n");
    MathString* res;
    while (operArray->length != 0) {
        int count = (int)operArray->length;
        for (int i =count-1 ; i>=0;i--) {
            getStackValueAtIndex(&temp, i, operArray);
            if (temp->numberOfNumsPointToOperator == 2) {
                res = calculate(temp);
                popStackAtIndex(&temp, i, operArray);
                deleteJinObject(temp);
                popStackAtIndex(&temp, res->index+1, numArray);
                deleteJinObject(temp);
                popStackAtIndex(&temp, res->index, numArray);
                deleteJinObject(temp);
                pushStackAtIndex(&res, res->index, numArray);
            }
        }
        if (numArray->length == 1) {
            break;
        }
        connectNumberAndOperator();
        //printStack(operArray);
        //printf("------------------------------------------\n");
    }
    getStackValueAtIndex(&res, numArray->length-1, numArray);
    if (isOverFlowed) {
        decreaseLevel();
        return INFINITY;
    }
    if (res) {
        result=res->string;
    }
    decreaseLevel();
    return result;
}

double evaluate(char* expression){
    if (expression == NULL)
    {
        printf("Input NULL.\n");
        return 0;
    }
    if (PrandNotEqual(expression)) {
        printf("parentheses do not match!\n");
        return 0;
    }
    inLevel = -1;
    isOverFlowed = false;
    char* s = replaceStr(expression, "pi", pi);
    expression = replaceStr(s, " ", "");
    free(s);
    double result = compute(expression);
    free(expression);
    return result;
}


