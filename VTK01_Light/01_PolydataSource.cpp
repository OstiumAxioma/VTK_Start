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
	//����һ��׶��
	vtkSmartPointer<vtkConeSource> coneSource = vtkSmartPointer<vtkConeSource>::New();
	coneSource->SetCenter(0, 0, 0);
	coneSource->SetRadius(5);
	coneSource->SetHeight(10);
	coneSource->SetResolution(10);
	coneSource->SetAngle(30);
	coneSource->SetDirection(0, 1, 0);//��ʾ����

	//Updateһ��Ҫ��,��������Դ
	coneSource->Update();

	//Polydata���ݽṹ��vtk��һ����Ҫ���ݽṹ
	vtkSmartPointer<vtkPolyData> cone = coneSource->GetOutput();

	int nPoints = cone->GetNumberOfPoints();
	int nCells = cone->GetNumberOfCells();
	int nVerts = cone->GetNumberOfVerts();

	std::cout << "nPoints: " << nPoints << std::endl;
	std::cout << "nCells: " << nCells << std::endl;
	std::cout << "nVerts: " << nVerts << std::endl;

	//������Ⱦ���ߣ�����vtkPolyDataMapper�������ڽ���vtkPolyDataͼ��������ʵ��ͼ�����ݵ���ȾͼԪ��ת��
	vtkSmartPointer<vtkPolyDataMapper> coneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	coneMapper->SetInputData(cone);//��PolyData����Դ

	//����Actor����
	vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
	coneActor->SetMapper(coneMapper);//��Mapper����
	coneActor->GetProperty()->SetColor(1, 0, 0);//������ɫ
	coneActor->GetProperty()->SetOpacity(0.5);//����͸����

	//������Ⱦ��Renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(coneActor);//���Actor
	renderer->SetBackground(1.0, 1.0, 0.0);//���ñ�����ɫ

	renderer->ResetCamera();

	//������Ⱦ����
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);//�����Ⱦ��
	renderWindow->SetSize(640, 480);//���ô��ڴ�С
	renderWindow->SetWindowName("PolyData Example");//���ô�������

	//������Ⱦ���ڽ�����
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);//����Ⱦ����

	//���ý�������ʽ
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

	renderWindowInteractor->SetInteractorStyle(style);//�󶨽�������ʽ

	renderWindow->Render();//��Ⱦ����
	renderWindowInteractor->Start();//��ʼ����

	//���Է�֧
}