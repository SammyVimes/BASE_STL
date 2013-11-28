#ifndef GRAPHVISUALIZATION_H
#define GRAPHVISUALIZATION_H

#include "BinaryTree.h"
#include "AVLTree.h"
#include <QueryVector.h>
#include <QueryList.h>
#include <cstdio>
#include <stdio.h>
#include <QFileDialog>
#include <QPainter>
#include <QPointF>
#include <algorithm>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
using namespace std;

class GraphVisualization
{
public:

    GraphVisualization();

    static void drawBinaryTree(BinaryTree<char>* tree, QGraphicsScene* scene){
        scene->clear();
        QueryVector<Node<char>*>* query = new QueryVector<Node<char>*>();
        QueryVector<QPoint*>* pointQuery = new QueryVector<QPoint*>();
        query->add(tree->getRoot());
        QPoint* parentPoint = new QPoint(0, 0);
        QPoint* lastOnLine = NULL;
        pointQuery->add(parentPoint);
        int modifier = 1;
        QGraphicsTextItem* item = scene->addText(QString(tree->getRoot()->get()));
        item->setPos(parentPoint->x(), parentPoint->y());
        bool first = true;
        int childQ = 1;
        int tmpQ = 0;
        while (true) {
            if (childQ == 0) {
                childQ = tmpQ;
                tmpQ = 0;
                modifier = modifier*1.5;
                lastOnLine = NULL;
            }
            QPoint* parentPoint = pointQuery->get();
            Node<char>* parent = query->get();
            if (!parent) {
                break;
            }
            if (parent->getLeft()) {
                QGraphicsTextItem* left = scene->addText(QString(parent->getLeft()->get()));
                /*Calculating offsets. No magic goes here, simple math*/
                int predictedX = parentPoint->x() - modifier*15;
                int finalX = predictedX;
                if (!first && lastOnLine) {
                    int xLastOnLine = lastOnLine->x();
                    if (predictedX <= xLastOnLine + 15) {
                        finalX = xLastOnLine + 20;
                    }
                }

                QPoint* leftChild = new QPoint(finalX, parentPoint->y() + 25);
                if (first) {
                    leftChild = new QPoint(parentPoint->x() - 60, parentPoint->y() + 25);
                }
                lastOnLine = leftChild;
                tmpQ++;
                left->setPos(leftChild->x(), leftChild->y());
                scene->addLine(parentPoint->x()+5, parentPoint->y()+18, leftChild->x()+8, leftChild->y()+5);
                pointQuery->add(leftChild);
                query->add(parent->getLeft());
            }
            if (parent->getRight()) {
                QGraphicsTextItem* right = scene->addText(QString(parent->getRight()->get()));
                int predictedX = parentPoint->x() + modifier*15;
                int finalX = predictedX;
                if (lastOnLine) {
                    int xLastOnLine = lastOnLine->x();
                    if (predictedX <= xLastOnLine + 15) {
                        finalX = xLastOnLine + 20;
                    }
                }

                QPoint* rightChild = new QPoint(finalX, parentPoint->y() + 25);
                if (first) {
                    rightChild = new QPoint(parentPoint->x() + 60, parentPoint->y() + 25);
                }
                tmpQ++;
                right->setPos(rightChild->x(), rightChild->y());
                scene->addLine(parentPoint->x()+5, parentPoint->y()+18, rightChild->x()+8, rightChild->y()+5);
                pointQuery->add(rightChild);
                query->add(parent->getRight());
                lastOnLine = rightChild;
            }
            first = false;
            childQ--;
        }
    }

    static void drawAVLTree(AVLTree<int>* tree, QGraphicsScene* scene){
        scene->clear();
        QueryList<AVLNode<int>*>* query = new QueryList<AVLNode<int>*>();
        QueryList<QPoint*>* pointQuery = new QueryList<QPoint*>();
        query->add(tree->getRoot());
        QPoint* parentPoint = new QPoint(0, 0);
        QPoint* lastOnLine = NULL;
        pointQuery->add(parentPoint);
        int modifier = 3;
        QGraphicsTextItem* item = scene->addText(QString("%1").arg(tree->getRoot()->getKey()));
        item->setPos(parentPoint->x(), parentPoint->y());
        bool first = true;
        int childQ = 1;
        int tmpQ = 0;
        while (true) {
            if (childQ == 0) {
                childQ = tmpQ;
                tmpQ = 0;
                lastOnLine = NULL;
            }
            QPoint* parentPoint = pointQuery->get();
            AVLNode<int>* parent = query->get();
            if (!parent) {
                break;
            }
            if (parent->getLeft()) {
                AVLNode<int>* l = parent->getLeft();
                int k = l->getKey();
                QGraphicsTextItem* left = scene->addText(QString("%1").arg(k));
                /*Calculating offsets. No magic goes here, simple math*/
                int predictedX = parentPoint->x() - modifier*15;
                int finalX = predictedX;
                if (!first && lastOnLine) {
                    int xLastOnLine = lastOnLine->x();
                    if (predictedX <= xLastOnLine + 35) {
                        finalX = xLastOnLine + 40;
                    }
                }

                QPoint* leftChild = new QPoint(finalX, parentPoint->y() + 25);
                if (first) {
                    leftChild = new QPoint(parentPoint->x() - 60, parentPoint->y() + 25);
                }
                lastOnLine = leftChild;
                tmpQ++;
                left->setPos(leftChild->x(), leftChild->y());
                scene->addLine(parentPoint->x()+5, parentPoint->y()+18, leftChild->x()+8, leftChild->y()+5);
                pointQuery->add(leftChild);
                query->add(parent->getLeft());
            }
            if (parent->getRight()) {
                QGraphicsTextItem* right = scene->addText(QString("%1").arg(parent->getRight()->getKey()));
                int predictedX = parentPoint->x() + modifier*15;
                int finalX = predictedX;
                if (lastOnLine) {
                    int xLastOnLine = lastOnLine->x();
                    if (predictedX <= xLastOnLine + 35) {
                        finalX = xLastOnLine + 40;
                    }
                }

                QPoint* rightChild = new QPoint(finalX, parentPoint->y() + 25);
                if (first) {
                    rightChild = new QPoint(parentPoint->x() + 60, parentPoint->y() + 25);
                }
                tmpQ++;
                right->setPos(rightChild->x(), rightChild->y());
                scene->addLine(parentPoint->x()+5, parentPoint->y()+18, rightChild->x()+8, rightChild->y()+5);
                pointQuery->add(rightChild);
                query->add(parent->getRight());
                lastOnLine = rightChild;
            }
            first = false;
            childQ--;
        }
    }

    static QPoint* drawAVLTreeRecursively(AVLNode<int>* node, QGraphicsScene* scene, int &x, int depth){
        AVLNode<int>* left = node->getLeft();
        QPoint* toTheLeft = 0;
        QPoint* toTheRight = 0;
        if (left) {
            toTheLeft = drawAVLTreeRecursively(left, scene, x, depth + 1);
        }
        QGraphicsTextItem* thisItem = scene->addText(QString("%1").arg(node->getKey()));
        QPoint* cc = new QPoint(x * 20, depth * 20);
        thisItem->setPos(cc->x(), cc->y());
        QPointF p = thisItem->pos();
        x++;
        AVLNode<int>* right = node->getRight();
        if (right) {
            toTheRight = drawAVLTreeRecursively(right, scene, x, depth + 1);
        }
        QPoint retPoint = p.toPoint();
        QPoint* ret = new QPoint(retPoint.x(), retPoint.y());
        if (toTheLeft) {
            scene->addLine(ret->x() + 15, ret->y() + 18, toTheLeft->x() + 18, toTheLeft->y() + 5);
        }
        if (toTheRight) {
            scene->addLine(ret->x() + 15, ret->y() + 18, toTheRight->x() + 18, toTheRight->y() + 5);
        }
        return ret;
    }


private:
  QGraphicsScene scene;

};

#endif // GRAPHVISUALIZATION_H
