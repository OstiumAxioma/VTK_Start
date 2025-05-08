#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);   // VTK was built with vtkRenderingOpenGL
VTK_MODULE_INIT(vtkInteractionStyle);

#include<vtkSmartPointer.h>
#include<vtkRenderWindow.h>
#include<vtkRenderer.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkInteractorStyleMultiTouchCamera.h>
#include<vtkPolyData.h>
#include<vtkOpenGLProperty.h>
#include<vtkCylinderSource.h>
#include<vtkConeSource.h>
#include<vtkCubeSource.h>
#include<vtkPolyDataMapper.h>
#include<vtkActor.h>
#include<iostream>
#include <vtkProperty.h>

int main(int argc, char* argv[])
{
	//定义一个锥体
	vtkSmartPointer<vtkConeSource> coneSource = vtkSmartPointer<vtkConeSource>::New();
	coneSource->SetCenter(0, 0, 0);
	coneSource->SetRadius(5);
	coneSource->SetHeight(10);
	coneSource->SetResolution(10);
	coneSource->SetAngle(30);
	coneSource->SetDirection(0, 1, 0);//显示方向

	//Update一定要有,更新数据源
	coneSource->Update();

	//Polydata数据结构是vtk的一个重要数据结构
	vtkSmartPointer<vtkPolyData> cone = coneSource->GetOutput();

	int nPoints = cone->GetNumberOfPoints();
	int nCells = cone->GetNumberOfCells();
	int nVerts = cone->GetNumberOfVerts();

	std::cout << "nPoints: " << nPoints << std::endl;
	std::cout << "nCells: " << nCells << std::endl;
	std::cout << "nVerts: " << nVerts << std::endl;

	//建立渲染管线，定义vtkPolyDataMapper对象，用于接受vtkPolyData图形数据以实现图形数据到渲染图元的转换
	vtkSmartPointer<vtkPolyDataMapper> coneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	coneMapper->SetInputData(cone);//绑定PolyData数据源

	//建立Actor对象
	vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
	coneActor->SetMapper(coneMapper);//绑定Mapper对象
	coneActor->GetProperty()->SetColor(1, 0, 0);//设置颜色
	coneActor->GetProperty()->SetOpacity(0.5);//设置透明度

	//创建渲染器Renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(coneActor);//添加Actor
	renderer->SetBackground(1.0, 1.0, 0.0);//设置背景颜色

	renderer->ResetCamera();

	//创建渲染窗口
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);//添加渲染器
	renderWindow->SetSize(640, 480);//设置窗口大小
	renderWindow->SetWindowName("PolyData Example");//设置窗口名称

	//创建渲染窗口交互器
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);//绑定渲染窗口

	//设置交互器样式
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

	renderWindowInteractor->SetInteractorStyle(style);//绑定交互器样式

	renderWindow->Render();//渲染窗口
	renderWindowInteractor->Start();//开始交互

	//测试分支
}