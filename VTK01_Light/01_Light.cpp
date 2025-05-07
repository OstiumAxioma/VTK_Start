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

	//1.  vtkCylinderSource  �̳���  vtkPolyDataAlgorithm
	//��������Ⱦ������ԭ�������
	vtkSmartPointer<vtkCylinderSource>  cylinder = vtkSmartPointer<vtkCylinderSource>::New();
	cylinder->SetCenter(0, 0, 0);
	cylinder->SetHeight(8.0);
	cylinder->SetRadius(3);
	cylinder->SetResolution(100);//�������Ķ���εı���
	cylinder->Update();


	vtkSmartPointer<vtkCubeSource>  cube = vtkSmartPointer<vtkCubeSource>::New();
	cube->SetCenter(10, 10, 10);
	cube->SetXLength(10);


	//2.��Ⱦ����μ�������

	//���������ݽ�����Ⱦ
	//cylinerMapper->SetInputConnection(����������ӿ�
	//cylinder->GetOutputPort()                 ���ӻ����ߵ�������ݽӿ�

	vtkSmartPointer<vtkPolyDataMapper>  cylinerMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	///	cylinerMapper->SetInputConnection(cylinder->GetOutputPort());
	cylinerMapper->SetInputData(cylinder->GetOutput());


	vtkSmartPointer<vtkPolyData>  data = cylinder->GetOutput();

	vtkSmartPointer<vtkPolyDataMapper>  cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInputConnection(cube->GetOutputPort());


	// cylinerMapper->SetInputData(PolyData);
	// cylinerMapper->SetInputData(cylinder->GetOutput());

	//3. �����ݿ��ӻ����(��Ա)

	vtkSmartPointer<vtkActor>   cylinderActor = vtkSmartPointer<vtkActor>::New();
	cylinderActor->SetMapper(cylinerMapper);//
	cylinderActor->GetProperty()->SetOpacity(1);


	vtkSmartPointer<vtkActor>   cubeActor = vtkSmartPointer<vtkActor>::New();
	cubeActor->SetMapper(cubeMapper);
	cubeActor->GetProperty()->SetColor(1, 1, 1);



	//4. ����������Ⱦ���̣���̨��
	vtkSmartPointer<vtkRenderer>  renderer = vtkSmartPointer<vtkRenderer>::New();



	renderer->RemoveAllViewProps();
	renderer->AddActor(cylinderActor);
	renderer->AddActor(cubeActor);
	//renderer->SetBackground(0.5, 0.6, 0.1);


	renderer->RemoveAllLights();



	//5.��ʾ���ڣ���Ժ��
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(renderer);
	renWin->SetSize(500, 500);
	renWin->SetWindowName("VTK");




	//6.  ��� ���� ����(��Ա�͹��ڵĽ���)
	vtkSmartPointer<vtkRenderWindowInteractor>  iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	//���ڵ��۾�
	//vtkSmartPointer<vtkInteractorStyleTrackballCamera>  style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	//iren->SetInteractorStyle(style);

	iren->Initialize();
	iren->Start();

}