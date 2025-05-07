#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);   // VTK was built with vtkRenderingOpenGL
VTK_MODULE_INIT(vtkInteractionStyle);
#include <vtkSmartPointer.h>
#include <vtkJPEGReader.h>
#include <vtkTexture.h>
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

//测试文件：data/texture.jpg
int main(int argc, char* argv[])
{
	//1.读入一幅纹理贴图
	vtkSmartPointer< vtkJPEGReader > reader = vtkSmartPointer< vtkJPEGReader >::New();
	reader->SetFileName("texture.jpg");


	//2. 定义纹理类对象
	vtkSmartPointer< vtkTexture > texture = vtkSmartPointer< vtkTexture >::New();
	texture->SetInputConnection(reader->GetOutputPort());
	texture->InterpolateOn();
	texture->SetColorModeToDefault();



	//3.贴图的平面
	vtkSmartPointer< vtkPlaneSource > plane = vtkSmartPointer< vtkPlaneSource >::New();



	vtkSmartPointer< vtkPolyDataMapper > mapper = vtkSmartPointer< vtkPolyDataMapper >::New();
	mapper->SetInputConnection(plane->GetOutputPort());

	vtkSmartPointer< vtkActor > actor = vtkSmartPointer< vtkActor >::New();
	actor->SetMapper(mapper);
	actor->SetTexture(texture);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(renderer);
	renWin->SetSize(640, 480);
	renWin->Render();
	renWin->SetWindowName("TextureExample");

	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	iren->Initialize();
	iren->Start();

	return EXIT_SUCCESS;



}