#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkAxesActor.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>

#include <vtkTransform.h>
#include <vtkAxesActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkLine.h>
#include <iostream>

#include <vector>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    vtkPoints * puntos =vtkPoints::New();

    for(double i=0; i<5;i++){
       double p[3] = {0.0,i,i*i};
      puntos->InsertNextPoint(p);
    }


    vtkCellArray * lines =vtkCellArray::New();

    for(unsigned int i = 0; i < 5; i++)
     {
       vtkLine * line = vtkLine::New();
       line->GetPointIds()->SetId(i,i);
       lines->InsertNextCell(line);
    }

    vtkPolyData * linesPolyData = vtkPolyData::New();

      // Add the points to the dataset
      linesPolyData->SetPoints(puntos);

      // Add the lines to the dataset
      linesPolyData->SetLines(lines);

     vtkPolyDataMapper * mapper = vtkPolyDataMapper::New();
      mapper->SetInputData(linesPolyData);

       vtkActor * actor  = vtkActor::New();
       actor->SetMapper(mapper);


     vtkSmartPointer<vtkSphereSource> sphereSource =
     vtkSmartPointer<vtkSphereSource>::New();
     sphereSource->SetCenter(0.0, 0.0, 0.0);
     sphereSource->SetRadius(0.5);

     //create a mapper
     vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
       vtkSmartPointer<vtkPolyDataMapper>::New();
     sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

     // create an actor
     vtkSmartPointer<vtkActor> sphereActor =
       vtkSmartPointer<vtkActor>::New();
     sphereActor->SetMapper(sphereMapper);

     // a renderer and render window
     vtkSmartPointer<vtkRenderer> renderer =
       vtkSmartPointer<vtkRenderer>::New();
     this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);



     // add the actors to the scene
    // renderer->AddActor(sphereActor);
     renderer->AddActor(actor);

     renderer->SetBackground(.1,.2,.3); // Background dark blue

     vtkSmartPointer<vtkTransform> transform =
       vtkSmartPointer<vtkTransform>::New();
     transform->Translate(0.0, 0.0, 0.0);

     vtkSmartPointer<vtkAxesActor> axes =
       vtkSmartPointer<vtkAxesActor>::New();

     // The axes are positioned with a user transform
     axes->SetUserTransform(transform);

     // properties of the axes labels can be set as follows
     // this sets the x axis label to red
     // axes->GetXAxisCaptionActor2D()->GetCaptionTextProperty()->SetColor(1,0,0);

     // the actual text of the axis label can be changed:
      axes->SetXAxisLabelText("Eje X");

     renderer->AddActor(axes);

     renderer->ResetCamera();
     this->ui->qvtkWidget->GetRenderWindow()->Render();

      // VTK/Qt wedded

     // this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(ren1);
     // this->ui->qvtkWidget->GetRenderWindow()->Render();

      // Set up action signals and slots
      //connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
