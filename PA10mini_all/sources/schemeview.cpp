#include "schemeview.h"

void exportPics()
{
    QPen pen;
    int a =128;
    pen.setWidthF(4.5);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    QPixmap pix(2*a, a);
    QPainter * painter = new QPainter(&pix);
    painter->translate(a, a/2);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen(pen);
    QColor col(255,255,255,255);

    pix.fill(col);
    //resistance
    painter->drawRect(QRectF(a*-0.3, a*-0.15, a*0.6, a*0.3));
    painter->drawLine(QLineF(a*-0.8, a*0.0, a*-0.3, a*0.0));
    painter->drawLine(QLineF(a*0.3, a*0.0, a*0.8, a*0.0));

    pix.save("Resources/SchemeEditor/R.png", "PNG");
    pix.fill(col);
    //capacitor
    painter->drawLine(QLineF(a*-0.8, a*0.0, a*-0.1, a*0.0));
    painter->drawLine(QLineF(a*0.1, a*0.0, a*0.8, a*0.0));

    painter->drawLine(QLineF(a*-0.1, a*-0.2, a*-0.1, a*0.2));
    painter->drawLine(QLineF(a*0.1, a*-0.2, a*0.1, a*0.2));

    pix.save("Resources/SchemeEditor/C.png", "PNG");
    pix.fill(col);
    //inductance
    painter->drawLine(QLineF(a*-0.8, a*0.0, a*-0.4, a*0.0));
    painter->drawLine(QLineF(a*0.4, a*0.0, a*0.8, a*0.0));

    painter->drawArc(QRectF(a*-0.4, a*-0.1, a*0.2, a*0.2), a*0*16, 180*16);
    painter->drawArc(QRectF(a*-0.2, a*-0.1, a*0.2, a*0.2), a*0*16, 180*16);
    painter->drawArc(QRectF(a*0.0, a*-0.1, a*0.2, a*0.2), a*0*16, 180*16);
    painter->drawArc(QRectF(a*0.2, a*-0.1, a*0.2, a*0.2), a*0*16, 180*16);

    pix.save("Resources/SchemeEditor/L.png", "PNG");
    pix.fill(col);
    //conduction
    painter->drawRect(QRectF(a*-0.3, a*-0.15, a*0.6, a*0.3));
    painter->drawLine(QLineF(a*-0.8, a*0.0, a*-0.3, a*0.0));
    painter->drawLine(QLineF(a*0.3, a*0.0, a*0.8, a*0.0));

    painter->drawLine(QLineF(a*-0.3, a*-0.15, a*0.3, a*0.15));
    painter->drawLine(QLineF(a*-0.3, a*0.15, a*0.3, a*-0.15));

    pix.save("Resources/SchemeEditor/G.png", "PNG");
    pix.fill(col);
    //voltage

    painter->drawLine(QLineF(a*-0.8, a*0.0, a*0.8, a*0.0));

    painter->drawEllipse(QRectF(a*-0.25, a*-0.25, a*0.5, a*0.5));

    painter->drawLine(QLineF(a*-0.05, a*-0.1, a*-0.2, a*0.0));
    painter->drawLine(QLineF(a*-0.05, a*0.1, a*-0.2, a*0.0));

    pix.save("Resources/SchemeEditor/E.png", "PNG");
    pix.fill(col);
    //current

    painter->drawLine(QLineF(a*-0.8, a*0.0, a*0.8, a*0.0));

    painter->drawEllipse(QRectF(a*-0.25, a*-0.25, a*0.5, a*0.5));

    painter->drawLine(QLineF(a*-0.15, a*-0.1, a*0.0, a*0.0));
    painter->drawLine(QLineF(a*0.0, a*0.0, a*-0.15, a*0.1));

    painter->drawLine(QLineF(a*0.05, a*-0.1, a*0.2, a*0.0));
    painter->drawLine(QLineF(a*0.2, a*0.0, a*0.05, a*0.1));

    pix.save("Resources/SchemeEditor/I.png", "PNG");
    pix.fill(col);
    painter->fillRect(QRectF(a*-0.05, a*-0.05, a*0.1, a*0.1), Qt::black);
    painter->drawRect(QRectF(a*-0.05, a*-0.05, a*0.1, a*0.1).adjusted(a*-0.1, a*-0.1, a*0.1, a*0.1));
    pix.save("Resources/SchemeEditor/Ungrounded.png", "PNG");
    pix.fill(col);
    painter->translate(0, -a/4);

    painter->fillRect(QRectF(a*-0.05, a*-0.05, a*0.1, a*0.1), Qt::black);
    painter->drawRect(QRectF(a*-0.05, a*-0.05, a*0.1, a*0.1).adjusted(a*-0.1, a*-0.1, a*0.1, a*0.1));
    painter->drawLine(QLineF(a*0.0, a*0.0, a*0.0, a*0.6));
    painter->drawLine(QLineF(a*-0.3, a*0.35, a*0.3, a*0.35));
    painter->drawLine(QLineF(a*-0.2, a*0.45, a*0.2, a*0.45));
    painter->drawLine(QLineF(a*-0.1, a*0.55, a*0.1, a*0.55));
    pix.save("Resources/SchemeEditor/Grounded.png", "PNG");
}


SchemeView::SchemeView(QWidget *parent)
    : QGraphicsView(parent)
{
    exportPics();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFrameShape(QFrame::NoFrame);
    setScene(new QGraphicsScene());

    isGrabbed = false;
    isScaled = false;

    //setRenderHint(QPainter::Antialiasing);

//numbers...
    gridW = 15;
    gridH = 10;
    scaleStep = 0.05;

//drawing grid
    setSceneRect(-1, -1, gridW+2, gridH+2);
    QList<QGraphicsLineItem *> gridLines;
    QPen gridPen;
    gridPen.setColor(QColor(222,222,222,255));
    //gridPen.setStyle(Qt::DashLine);

    for(double x = 0; x <= gridW; x+=1.0)
        gridLines.push_back(scene()->addLine(x, 0.0, x, gridH, gridPen));
    for(double y = 0; y <= gridH; y+=1.0)
        gridLines.push_back(scene()->addLine(0.0, y, gridW, y, gridPen));
    installEventFilter(this);

    //settin up menus
    //item
    itemMenu = new QMenu(this);

    QAction* rotateAction;
    rotateAction = new QAction("Rotate", this);
    connect(rotateAction, SIGNAL(triggered()), this, SLOT(rotateItem()));
    itemMenu->addAction(rotateAction);

    QAction* editAction;
    editAction = new QAction("Edit", this);
    connect(editAction, SIGNAL(triggered()), this, SLOT(editCircuitItem()));
    itemMenu->addAction(editAction);

    QAction* deleteAction;
    deleteAction = new QAction("Delete", this);
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));
    itemMenu->addAction(deleteAction);
    //node
    nodeMenu = new QMenu(this);

    QAction* groundAction;
    groundAction = new QAction("Ground", this);
    connect(groundAction, SIGNAL(triggered()), this, SLOT(groundNode()));
    nodeMenu->addAction(groundAction);

    QAction* ungroundAction;
    ungroundAction = new QAction("Unground", this);
    connect(ungroundAction, SIGNAL(triggered()), this, SLOT(ungroundNode()));
    nodeMenu->addAction(ungroundAction);

    //main
    mainMenu = new QMenu(this);

    QAction* addRAction;
    addRAction = new QAction("Add R", this);
    connect(addRAction, SIGNAL(triggered()), this, SLOT(addR()));
    mainMenu->addAction(addRAction);

    QAction* addGAction;
    addGAction = new QAction("Add G", this);
    connect(addGAction, SIGNAL(triggered()), this, SLOT(addG()));
    mainMenu->addAction(addGAction);

    QAction* addLAction;
    addLAction = new QAction("Add L", this);
    connect(addLAction, SIGNAL(triggered()), this, SLOT(addL()));
    mainMenu->addAction(addLAction);

    QAction* addCAction;
    addCAction = new QAction("Add C", this);
    connect(addCAction, SIGNAL(triggered()), this, SLOT(addC()));
    mainMenu->addAction(addCAction);

    QAction* addEAction;
    addEAction = new QAction("Add E", this);
    connect(addEAction, SIGNAL(triggered()), this, SLOT(addU()));
    mainMenu->addAction(addEAction);

    QAction* addIAction;
    addIAction = new QAction("Add I", this);
    connect(addIAction, SIGNAL(triggered()), this, SLOT(addI()));
    mainMenu->addAction(addIAction);
}

void SchemeView::deleteItem()
{
    CircuitItem* element;

    foreach(element, elements)
    {
        if(qgraphicsitem_cast<CircuitItem*>(hoveredItem)->getId() == element->getId() &&
            qgraphicsitem_cast<CircuitItem*>(hoveredItem)->elementType() == element->elementType()) // cHANGE: && to ==
        {
            elements.removeOne(element);
            delete element;
        }
    }
    checkgrid();
}

void SchemeView::editCircuitItem()
{
    CircuitItemEdit *tmp = new CircuitItemEdit(reinterpret_cast<CircuitItem*>(hoveredItem));
    tmp->move(lastMousePos);
    tmp->show();
}

void SchemeView::groundNode()
{
    reinterpret_cast<CircuitNodeItem*>(hoveredItem)->setGround(true);
}

void SchemeView::ungroundNode()
{
    reinterpret_cast<CircuitNodeItem*>(hoveredItem)->setGround(false);
}

SchemeView::~SchemeView()
{

}

void SchemeView::checkgrid()
{
    QList<QGraphicsItem*> items;
    QGraphicsItem* item;
    CircuitNodeItem* node;
    for(int i=0; i <= gridH; ++i)
    {
        for(int j=0; j <= gridW; ++j)
        {
            int counter = 0;
            items = scene()->items(CircuitItem::contactRect().translated(j, i));
            int id = -1;
            foreach(item, items)
            {
                if(item->type() == CircuitItem::CircuitItemType)
                {
                    if(reinterpret_cast<CircuitItem*>(item)->contact(QPointF(j,i)) != -1)
                        counter++;
                }
                else if(item->type() == CircuitItem::CircuitItemNodeType)
                {
                    id = reinterpret_cast<CircuitNodeItem*>(item)->getId();
                }
            }

            if(id == -1 && counter >= 2)
            {
                addNode(QPointF(j, i));
            }
            else if (id != -1 && counter < 2)
            {
                foreach(node, nodes)
                {
                    if(node->getId() == id)
                    {
                        nodes.removeOne(node);
                        delete node;
                    }
                }
            }
        }
    }
}
void SchemeView::addNode(QPointF pos)
{
    CircuitNodeItem* node;
    int newId = 1;
    bool stop = false;
    while(!stop)
    {
        stop = true;
        foreach(node, nodes)
            if(newId == node->getId())
                stop = false;
        if(!stop)
            ++newId;
    }
    nodes.push_back(new CircuitNodeItem(newId, pos));
    scene()->addItem(nodes.last());
}

QString SchemeView::getSystem()
{
    QString result;
    CircuitItem* element;
    CircuitNodeItem* node;
//dPhi and element equals
    foreach(element, elements)
    {
        result.append(element->equal() + "\n");
        result.append(element->getu() + "=");
        bool isFirstInLine = true;
        foreach(node, nodes)
        {
            if(!node->isGrounded())
            {
                int contact = element->contact(node->scenePos());
                qDebug() << contact;
                if(contact == 0)
                {
                    if(isFirstInLine)
                        isFirstInLine = false;
                    else
                        result.append("+");
                    result.append("phi" + QString::number(node->getId()));
                }
                if(contact == 1)
                {
                    isFirstInLine = false;
                    result.append("-");
                    result.append("phi" + QString::number(node->getId()));
                }
            }
        }
        result.append("\n");
    }
//Kirchhoff
    foreach(node, nodes)
    {
        bool isFirstInLine = true;
        if(!node->isGrounded())
        {
            foreach(element, elements)
            {
                int contact = element->contact(node->scenePos());
                if(contact == 0)
                {
                    if(isFirstInLine)
                        isFirstInLine = false;
                    else
                        result.append("+");
                    result.append(element->geti());
                }
                else if(contact == 1)
                {
                    isFirstInLine = false;
                    result.append("-");
                    result.append(element->geti());
                }
            }
        result.append("=0\n");
        }
    }
    foreach(element, elements)
    {
        if(element->u0.toDouble() != 0)
        {
            result.append(element->getu());
            result.append("==");
            result.append(element->u0);
            result.append("\n");
        }
        if(element->i0.toDouble() != 0)
        {
            result.append(element->geti());
            result.append("==");
            result.append(element->i0);
            result.append("\n");
        }
    }
    return result;
}

bool SchemeView::eventFilter(QObject *object, QEvent *event)
{
    if( event->type() == QEvent::Resize )
    {
        if(getScale() < fullScale())
        {
            setScale(fullScale());
        }
    }
    return false;
}


void SchemeView::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::MidButton)
    {
        setCursor(Qt::ClosedHandCursor);
        isGrabbed = true;
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
    lastMousePos = event->pos();
}

void SchemeView::rotateItem()
{
    static_cast<CircuitItem*>(hoveredItem)->rotateRight();
    checkgrid();
}
void SchemeView::mouseMoveEvent(QMouseEvent * event)
{
    if(isGrabbed)
    {
        int dx  = lastMousePos.x() - event->pos().x();
        int dy  = lastMousePos.y() - event->pos().y();
        QScrollBar* hBar = horizontalScrollBar();
        QScrollBar* vBar = verticalScrollBar();
        hBar->setValue(hBar->value() + dx);
        vBar->setValue(vBar->value() + dy);

        lastMousePos = event->pos();
    }
    else
    {
        QGraphicsView::mouseMoveEvent(event);
    }
}


void SchemeView:: mouseReleaseEvent( QMouseEvent * event )
{
    if(event->button() ==  Qt::MidButton)
    {
        setCursor(Qt::ArrowCursor);
        isGrabbed = false;
    }
    else if(event->button() ==  Qt::RightButton )
    {
        hoveredItem = scene()->itemAt(mapToScene(event->pos()), QTransform());
        if(hoveredItem != nullptr)
        {
            lastMousePos = event->globalPos();
            switch(hoveredItem->type())
            {
            case CircuitItem::CircuitItemType:
                itemMenu->exec(event->globalPos());
                break;
            case CircuitItem::CircuitItemNodeType:
                nodeMenu->exec(event->globalPos());
                break;
            }
        }
        else
        {
            lastMousePos = event->pos();
            mainMenu->exec(event->globalPos());
        }
    }
    else
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
}


void SchemeView::enterEvent (QEvent* event)
{
    Q_UNUSED(event)

    setMouseTracking(true);
}


void SchemeView::leaveEvent (QEvent* event)
{
    Q_UNUSED(event)

    setMouseTracking(false);
}


void SchemeView::wheelEvent ( QWheelEvent * event )
{
    qreal delta = (event->delta() > 0) ? scaleStep : -scaleStep;
    qreal scaleValue = getScale() * (1 + delta);
    if(scaleValue > fullScale())
    {
        setScale(scaleValue);
        isScaled = true;
    }
    else
    {
        setScale(fullScale());
        isScaled = false;
    }
}


qreal SchemeView::getScale()
{
    return transform().m11();
}

qreal SchemeView::fullScale()
{
    return sceneRect().height()/height()>sceneRect().width()/width()?height()/sceneRect().height():width()/sceneRect().width();
}

int SchemeView::recieveElementId(CircuitElementType type)
{
    CircuitItem* element;
    int newId = 1;
    bool stop = false;
    while(!stop)
    {
        stop = true;
        foreach(element, elements)
            if(newId == element->getId() && element->elementType() == type)
                stop = false;
        if(!stop)
            ++newId;
    }
    return newId;
}

void SchemeView::setScale (qreal s)
{
    QTransform tr = transform();
    tr.setMatrix(s, tr.m12(), tr.m13(),
                 tr.m21(), s, tr.m23(),
                 tr.m31(), tr.m32(), tr.m33());
    setTransform(tr);
}

void SchemeView::addR()
{
    int id = recieveElementId(CircuitElementType::R);
    RItem* tmp = new RItem(id, mapToScene(lastMousePos).toPoint());
    scene()->addItem(reinterpret_cast<QGraphicsLineItem*>(tmp));
    elements.push_back(reinterpret_cast<CircuitItem*>(tmp));
    checkgrid();
}

void SchemeView::addG()
{
    int id = recieveElementId(CircuitElementType::G);
    GItem* tmp = new GItem(id, mapToScene(lastMousePos).toPoint());
    scene()->addItem(reinterpret_cast<QGraphicsLineItem*>(tmp));
    elements.push_back(reinterpret_cast<CircuitItem*>(tmp));
    checkgrid();
}

void SchemeView::addL()
{
    int id = recieveElementId(CircuitElementType::L);
    LItem* tmp = new LItem(id, mapToScene(lastMousePos).toPoint());
    scene()->addItem(reinterpret_cast<QGraphicsLineItem*>(tmp));
    elements.push_back(reinterpret_cast<CircuitItem*>(tmp));
    checkgrid();
}

void SchemeView::addC()
{
    int id = recieveElementId(CircuitElementType::C);
    CItem* tmp = new CItem(id, mapToScene(lastMousePos).toPoint());
    scene()->addItem(reinterpret_cast<QGraphicsLineItem*>(tmp));
    elements.push_back(reinterpret_cast<CircuitItem*>(tmp));
    checkgrid();
}

void SchemeView::addU()
{
    int id = recieveElementId(CircuitElementType::E);
    EItem* tmp = new EItem(id, mapToScene(lastMousePos).toPoint());
    scene()->addItem(reinterpret_cast<QGraphicsLineItem*>(tmp));
    elements.push_back(reinterpret_cast<CircuitItem*>(tmp));
    checkgrid();
}

void SchemeView::addI()
{
    int id = recieveElementId(CircuitElementType::I);
    IItem* tmp = new IItem(id, mapToScene(lastMousePos).toPoint());
    scene()->addItem(reinterpret_cast<QGraphicsLineItem*>(tmp));
    elements.push_back(reinterpret_cast<CircuitItem*>(tmp));
    checkgrid();
}

