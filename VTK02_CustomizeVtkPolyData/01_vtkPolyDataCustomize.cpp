#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)   // VTK was built with vtkRenderingOpenGL
VTK_MODULE_INIT(vtkInteractionStyle)
VTK_MODULE_INIT(vtkRenderingFreeType)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)

#include<vtkSmartPointer.h>
#include<vtkPolygon.h>
#include<vtkTriangle.h>
#include<vtkCellarray.h>
#include<vtkPolyData.h>
#include<vtkPolyDataMapper.h>
#include<vtkRenderWindow.h>
#include<vtkRenderer.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkProperty.h>
#include<vtkActor.h>
#include<vtkFloatArray.h>

#include<iostream>

int main(int argc, char* argv[])
{
	//储存点集合
	double pts[5][3] = {
		{ 0, 0, 0 },
		{ 1, 0, 0 },
		{ 1, 1, 0 },
		{ 0, 1, 0 },
		{ 2, 0, 0 }
	};

	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();//创建点坐标数组

	//循环放入数组
	for (int i = 0; i < 5; i++)
	{
		cout << pts[i] << endl;
		points->InsertNextPoint(pts[i]);//插入点
	}

	//创建多边形
	vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();

	//创建Actor
	vtkSmartPointer<vtkActor> polygonActor = vtkSmartPointer<vtkActor>::New();


	//创建渲染器Renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(polygonActor);//添加Actor
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

	return EXIT_SUCCESS;
}