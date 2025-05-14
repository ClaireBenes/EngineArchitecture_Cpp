#pragma once

#include "IRenderer.h"
#include "Engine/Vertex/VertexArray.h"
#include "Engine/Shader/ShaderProgram.h"

#include <vector>

/*
RendererGL is an OpenGL-based renderer that implements IRenderer. It handles
OpenGL initialization, shader loading, and drawing of 2D/3D objects, including
sprites, meshes, and textures, using OpenGL API.
*/
class RendererGL : public IRenderer
{
public:
	/*
	 Constructor for RendererGL.
	 Initializes member variables and sets up OpenGL context.
	 */
	RendererGL();
	/*
	 Destructor for RendererGL.
	 Cleans up the OpenGL context and VertexArray objects.
	 */
	virtual ~RendererGL();

	// Deleted copy constructor and assignment operator to prevent copying
	RendererGL(const RendererGL&) = delete;
	RendererGL& operator=(const RendererGL&) = delete;

	/*
	 * Initializes the OpenGL renderer with the given window.
	 * @param rWindow The window to render the graphics onto.
	 * @return Returns true if initialization is successful, false otherwise.
	 */
	bool Initialize(Window& rWindow) override;
	/*
	 Loads the shaders used by the renderer for various components.
	 */
	void LoadShaders();
	/*
	 Begins the drawing process, clearing the screen and setting up necessary OpenGL states.
	 */
	void BeginDraw() override;
	/*
	 Draws all the rendered components (meshes, sprites, etc.).
	 */
	void Draw() override;
	/*
	 Ends the drawing process by swapping the buffers.
	 */
	void EndDraw() override;

	/*
	 * Draws a filled rectangle on the screen with the specified color.
	 * @param rRect The rectangle to be drawn.
	 * @param pColor The color of the rectangle.
	 */
	void DrawRect(const Rectangle& rRect, Color pColor) override;
	/*
	 * Draws the outline of a rectangle on the screen with the specified color.
	 * @param rRect The rectangle to be drawn.
	 * @param pColor The color of the rectangle outline.
	 */
	void DrawRectLine(const Rectangle& rRect, Color pColor) override;

	/*
	 Draws all sprites currently in the render queue.
	 */
	void DrawAllSprites();
	/*
	 * Draws a sprite on the screen using the specified texture and transformation.
	 * @param rOwner The actor owning the sprite (used for context, not directly here).
	 * @param rTexture Pointer to the texture to render.
	 * @param rec The rectangle that defines the position and size of the sprite on screen.
	 * @param flip Specifies sprite flipping (horizontal, vertical, etc.).
	 */
	void DrawSprite(const Actor& rOwner, Texture* rTexture, Rectangle rec, Flip flip = Flip::None) override;

	/*
	 Draws all meshes currently in the render queue.
	 */
	void DrawAllMeshes();
	/*
	 * Draws a mesh with the specified texture index and transformation.
	 * @param pMesh The mesh to be drawn.
	 * @param pTextureIndex The texture index of the mesh.
	 * @param transform The transformation matrix to apply to the mesh.
	 * @param tiling The tiling factor for the texture.
	 */
	void DrawMesh(Mesh* pMesh, int pTextureIndex, const Matrix4& transform, Vector2 tiling = Vector2::ONE) override;

	/*
	 * Sets the view matrix used for rendering.
	 * @param pView The new view matrix.
	 */
	void SetViewMatrix(const Matrix4& pView) override;

	/*
	 Closes the OpenGL context and cleans up resources.
	 */
	void Close() override;
	/*
	 * Returns the type of renderer (OpenGL).
	 * @return RendererType::OPENGL.
	 */
	RendererType GetType() override;

	/*
	 * Gets the cube mesh used for rendering.
	 * @return A pointer to the cube mesh.
	 */
	static Mesh* GetCubeMesh();

	// Static shader programs for different rendering effects
	static ShaderProgram mSimpleMeshShaderProgram; // Shader program for simple meshes.
	static ShaderProgram mTesselationMeshShaderProgram; // Shader program for tessellated meshes.
	static ShaderProgram mGrassShaderProgram; // Shader program for rendering grass.
	static ShaderProgram mSandShaderProgram; // Shader program for a displaced terrain using heightmap.

private:
	Window* mWindow; // The window to render to.
	VertexArray* mSpriteVao; // The vertex array for rendering sprites.
	SDL_GLContext mContext; // The OpenGL context used by the renderer.

	Matrix4 mSpriteViewProj; // The projection matrix for rendering sprites.
	Matrix4 mView; // The view matrix used for camera transformations.
	Matrix4 mProjection; // The projection matrix for 3D rendering.

	static Mesh* mCubeMesh; // The static cube mesh used for rendering.

	//ShaderProgram
	ShaderProgram mSpriteShaderProgram; // Shader program for rendering sprites.
	ShaderProgram mRectShaderProgram; // Shader program for rendering filled rectangles.
	ShaderProgram mRectLineShaderProgram;	// Shader program for rendering rectangle outlines
	ShaderProgram mTerrainShaderProgram; // Shader program for rendering terrain.
};


