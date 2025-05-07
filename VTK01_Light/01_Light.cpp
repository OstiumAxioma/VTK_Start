#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);   // VTK was built with vtkRenderingOpenGL
VTK_MODULE_INIT(vtkInteractionStyle);

#include<vtkSmartPointer.h>
#include<vtkRenderWindow.h>
#include<vtkRenderer.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkInteractorStyleMultiTouchCamera.h>
#include<vtkCylinderSource.h>
#include<vtkCubeSource.h>
#include<vtkPolyDataMapper.h>
#include<vtkActor.h>
#include<iostream>
#include <vtkProperty.h>
using namespace std;


void  main()
{

	//1.  vtkCylinderSource  继承自  vtkPolyDataAlgorithm
	//中心在渲染场景的原点的柱体
	vtkSmartPointer<vtkCylinderSource>  cylinder = vtkSmartPointer<vtkCylinderSource>::New();
	cylinder->SetCenter(0, 0, 0);
	cylinder->SetHeight(8.0);
	cylinder->SetRadius(3);
	cylinder->SetResolution(100);//柱面截面的多边形的边数
	cylinder->Update();


	vtkSmartPointer<vtkCubeSource>  cube = vtkSmartPointer<vtkCubeSource>::New();
	cube->SetCenter(10, 10, 10);
	cube->SetXLength(10);


	//2.渲染多边形几何数据

	//对输入数据进行渲染
	//cylinerMapper->SetInputConnection(）数据输入接口
	//cylinder->GetOutputPort()                 可视化管线的输出数据接口

	vtkSmartPointer<vtkPolyDataMapper>  cylinerMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	///	cylinerMapper->SetInputConnection(cylinder->GetOutputPort());
	cylinerMapper->SetInputData(cylinder->GetOutput());


	vtkSmartPointer<vtkPolyData>  data = cylinder->GetOutput();

	vtkSmartPointer<vtkPolyDataMapper>  cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInputConnection(cube->GetOutputPort());


	// cylinerMapper->SetInputData(PolyData);
	// cylinerMapper->SetInputData(cylinder->GetOutput());

	//3. 把数据可视化表达(演员)

	vtkSmartPointer<vtkActor>   cylinderActor = vtkSmartPointer<vtkActor>::New();
	cylinderActor->SetMapper(cylinerMapper);//
	cylinderActor->GetProperty()->SetOpacity(1);


	vtkSmartPointer<vtkActor>   cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);
	cubeActor->GetProperty()->SetColor(1, 1, 1);



	//4. 管理场景的渲染过程（舞台）
	vtkSmartPointer<vtkRenderer>  renderer = vtkSmartPointer<vtkRenderer>::New();



	renderer->RemoveAllViewProps();
	renderer->AddActor(cylinderActor);
	renderer->AddActor(cubeActor);
	//renderer->SetBackground(0.5, 0.6, 0.1);


	renderer->RemoveAllLights();



	//5.显示窗口（剧院）
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(renderer);
	renWin->SetSize(500, 500);
	renWin->SetWindowName("VTK");




	//6.  鼠标 键盘 交互(演员和观众的交互)
	vtkSmartPointer<vtkRenderWindowInteractor>  iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	//观众的眼睛
	//vtkSmartPointer<vtkInteractorStyleTrackballCamera>  style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	//iren->SetInteractorStyle(style);

	iren->Initialize();
	iren->Start();

}