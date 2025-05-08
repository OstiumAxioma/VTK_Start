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
	//����㼯��
	double pts[5][3] = {
		{ 0, 0, 0 },
		{ 1, 0, 0 },
		{ 1, 1, 0 },
		{ 0, 1, 0 },
		{ 2, 0, 0 }
	};

	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();//��������������

	//ѭ����������
	for (int i = 0; i < 5; i++)
	{
		cout << pts[i] << endl;
		points->InsertNextPoint(pts[i]);//�����
	}

	//���������
	vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();

	//����Actor
	vtkSmartPointer<vtkActor> polygonActor = vtkSmartPointer<vtkActor>::New();


	//������Ⱦ��Renderer
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(polygonActor);//���Actor
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

	return EXIT_SUCCESS;
}