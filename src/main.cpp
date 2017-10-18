#include <string>
#include <iostream>
#include <memory>
#include <stack>

using namespace std;

struct SArgumentNode;
struct SOperatorNode;

struct SVisitor {
  virtual void visitArgumentNode(SArgumentNode*) = 0;
  virtual void visitOperatorNode(SOperatorNode*) = 0;
  virtual string print() const = 0;
};

struct SNode {
  unique_ptr<SNode> left;
  unique_ptr<SNode> right;

  virtual void accept(shared_ptr<SVisitor>) = 0;
};

struct SArgumentNode : public SNode {
  double argument;

  SArgumentNode(double _argument) : argument(_argument) {}

  void accept(shared_ptr<SVisitor> v) override {
    v->visitArgumentNode(this);
  }
};

struct SOperatorNode : public SNode {
  char oper;

  SOperatorNode(char _oper) : oper(_oper){};

  void accept(shared_ptr<SVisitor> v) override {
    if (left != nullptr) {
      left->accept(v);
    }
    if (right != nullptr) {
      right->accept(v);
    }

    v->visitOperatorNode(this);
  }
};

struct SPostFixPrintVisitor : public SVisitor {
  string output;

  void visitArgumentNode(SArgumentNode* n) override {
    output += to_string(n->argument);
    output.append(" ");
  }

  void visitOperatorNode(SOperatorNode* n) override {
    output += n->oper;
    output.append(" ");
  }

  string print() const override {
    return output;
  }
};

struct SCalculateVisitor : public SVisitor {
  stack<double> calcStack;

  void visitArgumentNode(SArgumentNode* n) override {
    calcStack.push(n->argument);
  }

  void visitOperatorNode(SOperatorNode* n) override {
    auto a = calcStack.top();
    calcStack.pop();

    auto b = calcStack.top();
    calcStack.pop();

    switch (n->oper) {
      case '+':
        calcStack.push(b + a);
        break;
      case '-':
        calcStack.push(b - a);
        break;
    }
  }

  string print() const override {
    return to_string(calcStack.top());
  }
};

int main() {
  auto root = make_unique<SOperatorNode>('+');
  root->left = make_unique<SArgumentNode>(2.0);
  root->right = make_unique<SOperatorNode>('-');
  root->right->left = make_unique<SArgumentNode>(10.3);
  root->right->right = make_unique<SArgumentNode>(4.7);

  auto visitor = make_shared<SPostFixPrintVisitor>();
  root->accept(visitor);
  cout << visitor->print() << endl;

  auto visitor2 = make_shared<SCalculateVisitor>();
  root->accept(visitor2);
  cout << visitor2->print() << endl;
}
