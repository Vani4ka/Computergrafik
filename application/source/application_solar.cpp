#include "application_solar.hpp"
#include "launcher.hpp"

#include "utils.hpp"
#include "shader_loader.hpp"
#include "model_loader.hpp"

#include <glbinding/gl/gl.h>
// use gl definitions from glbinding 
using namespace gl;

//dont load gl bindings from glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <texture_loader.hpp>

ApplicationSolar::ApplicationSolar(std::string const& resource_path)
        :Application{resource_path}
        ,planet_object{}
{
    //we mentioned that the realistic solar system is not very.. pretty
    //so our solar system is not realistic scaled, but still fancy

    /*//Sun
    planets.push_back(Planet{0.6f, 1, 0, {1.0f, 0.647f,0.0f}});
    //Mercury
    planets.push_back(Planet{0.08f, 0.47f, 0.8f, {0.592f,0.509f,0.662f}});
    //Venus
    planets.push_back(Planet{0.13f, 0.35f, 1.1f, {0.8f,0.57f,0.035f}});
    //Earth
    Planet earth = Planet{0.14f, 0.3f, 1.5f, {0.08f,0.27f,0.61f}};
    //Moon
    earth.moons.push_back(Planet{0.04f, 1.0f, 0.2f, {0.77f,0.789f,0.82f}});
    planets.push_back(earth);
    //Mars
    planets.push_back(Planet{0.11f, 0.24f, 1.95f, {0.9f,0.356f,0.043f}});
    //Jupiter
    planets.push_back(Planet{0.32f, 0.13f, 2.65f, {0.46f,0.33f,0.18f}});
    //Saturn
    planets.push_back(Planet{0.25f, 0.1f, 3.35f, {0.46f,0.4f,0.325f}});
    //Uranus
    planets.push_back(Planet{0.17f, 0.07f, 3.9f, {0.1f,0.56f,0.9f}});
    //Neptune
    planets.push_back(Planet{0.17f, 0.055f, 4.3f, {0.13f,0.33f,0.87f}});*/

    std::cout<<"Loading "<<m_resource_path+"textures/sunmap.png\n";
    //Sun
    planets.push_back(
            Planet{0.6f, 1, 0, texture_loader::file(m_resource_path+"textures/sunmap.png")}
    );

    std::cout<<"Loading "<<m_resource_path+"textures/mercurymap.png\n";
    //Mercury
    planets.push_back(
            Planet{0.08f, 0.47f, 0.8f, texture_loader::file(m_resource_path+"textures/mercurymap.png")}
    );

    std::cout<<"Loading "<<m_resource_path+"textures/venusmap.png\n";
    //Venus
    planets.push_back(
            Planet{0.13f, 0.35f, 1.1f, texture_loader::file(m_resource_path+"textures/venusmap.png")}
    );

    std::cout<<"Loading "<<m_resource_path+"textures/earthmap1k.png\n";
    //Earth
    Planet earth = Planet{0.14f, 0.3f, 1.5f, texture_loader::file(m_resource_path+"textures/earthmap1k.png")};

    std::cout<<"Loading "<<m_resource_path+"textures/moonmap1k.png\n";
    //Moon
    earth.moons.push_back(
            Planet{0.04f, 1.0f, 0.2f, texture_loader::file(m_resource_path+"textures/moonmap1k.png")}
    );
    planets.push_back(earth);

    std::cout<<"Loading "<<m_resource_path+"textures/marsmap1k.png\n";
    //Mars
    planets.push_back(
            Planet{0.11f, 0.24f, 1.95f, texture_loader::file(m_resource_path+"textures/marsmap1k.png")}
    );

    std::cout<<"Loading "<<m_resource_path+"textures/jupitermap.png\n";
    //Jupiter
    planets.push_back(
            Planet{0.32f, 0.13f, 2.65f, texture_loader::file(m_resource_path+"textures/jupitermap.png")}
    );

    std::cout<<"Loading "<<m_resource_path+"textures/saturnmap.png\n";
    //Saturn
    planets.push_back(
            Planet{0.25f, 0.1f, 3.35f, texture_loader::file(m_resource_path+"textures/saturnmap.png")}
    );

    std::cout<<"Loading "<<m_resource_path+"textures/uranusmap.png\n";
    //Uranus
    planets.push_back(
            Planet{0.17f, 0.07f, 3.9f, texture_loader::file(m_resource_path+"textures/uranusmap.png")}
    );

    std::cout<<"Loading "<<m_resource_path+"textures/neptunemap.png\n";
    //Neptune
    planets.push_back(
            Planet{0.17f, 0.055f, 4.3f, texture_loader::file(m_resource_path+"textures/neptunemap.png")}
    );

    for(int i=0; i < 1000; i++){
        //coordinates X, Y, Z
        for(int j = 0; j < 3; j++){
            stars.push_back(
                    static_cast<float> (rand()) /
                            (static_cast<float>(RAND_MAX) / (20.0f)) - 10.0f
            );
        }

        //colors R, G, B
        for(int j = 0; j < 3; j++){
            stars.push_back(static_cast<float>(rand())/
                                    static_cast<float>(RAND_MAX));
        }
    }

    float x, z;
    for (int i = 0; i < 360; i+=1) {
        float rad = float(i*M_PI)/180.0f;

        x = (float)(cos(rad));
        z = (float)(sin(rad));

        orbit_vertices.push_back(x);
        orbit_vertices.push_back(0.0f);
        orbit_vertices.push_back(z);
    }

    view_horizontal_angle = 0.0f;
    view_vertical_angle = 0.0f;

    //1 for blinn-phong
    shadingMode = 1;

    initializeGeometry();
    initializeTextures();
    initializeShaderPrograms();
}

int ApplicationSolar::getIndexOf(Planet const &planet) const {
    for(int i=0; i< planets.size(); i++){
        if(&planets[i] == &planet){
            return i;
        }
    }

    std::cout<<"ERROR: Planet not found!\n";
    return -1;
}

void ApplicationSolar::render() const {
    for(auto const& planet: planets) {
        //transform matrix of planet to make moons rotate around planets
        glm::fmat4 transBase{};
        renderPlanet(planet, transBase);

        for(auto const& moon: planet.moons){
            //renderPlanet(moon, transBase);
        }

        renderOrbit(planet.orig_distance);
    }

    renderStars();
}

void ApplicationSolar::renderStars() const {
    glUseProgram(m_shaders.at("star").handle);
    glBindVertexArray(star_object.vertex_AO);
    glDrawArrays(star_object.draw_mode, 0, star_object.num_elements);
}

void ApplicationSolar::renderOrbit(float radius) const {
    glUseProgram(m_shaders.at("orbit").handle);
    uploadOrbitTransforms(radius);
    glBindVertexArray(orbit_object.vertex_AO);
    glDrawArrays(orbit_object.draw_mode, 0, orbit_object.num_elements);
}

void ApplicationSolar::renderPlanet(Planet const& planet, glm::fmat4& transBase) const {
    int index = getIndexOf(planet);

    glActiveTexture(texture_objects[index].target);
    glBindTexture(GL_TEXTURE_2D, texture_objects[index].handle);

    // bind shader to upload uniforms
    glUseProgram(m_shaders.at("planet").handle);

    uploadPlanetTransforms(planet, transBase);

    glUniform1i(m_shaders.at("planet").u_locs.at("ColorTex"), index);

    //Assign. 3 color upload
    //glUniform3fv(m_shaders.at("planet").u_locs.at("DiffuseColor"), 1, glm::value_ptr(planet.color));

    //upload shading mode
    glUniform1i(m_shaders.at("planet").u_locs.at("ShadingMode"), shadingMode);

    // bind the VAO to draw
    glBindVertexArray(planet_object.vertex_AO);

    // draw bound vertex array using bound shader
    glDrawElements(planet_object.draw_mode, planet_object.num_elements, model::INDEX.type, NULL);
}

//Assign. 1
void ApplicationSolar::uploadPlanetTransforms(Planet const &planet, glm::fmat4& transBase) const {
    glm::fmat4 model_matrix = glm::rotate(transBase, float(glfwGetTime()) * planet.rot_speed*2, glm::fvec3{0.0f, 1.0f, 0.0f});
    model_matrix = glm::translate(model_matrix, glm::fvec3{0.0f, 0.0f, - planet.orig_distance});
    transBase = model_matrix;

    model_matrix = glm::scale(model_matrix, glm::fvec3{planet.scale});

    glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ModelMatrix"),
                       1, GL_FALSE, glm::value_ptr(model_matrix));

    // extra matrix for normal transformation to keep them orthogonal to surface
    glm::fmat4 normal_matrix = glm::inverseTranspose(glm::inverse(m_view_transform) * model_matrix);
    glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("NormalMatrix"),
                       1, GL_FALSE, glm::value_ptr(normal_matrix));
}

void ApplicationSolar::uploadOrbitTransforms(float radius) const {
    glm::fmat4 model_matrix = glm::scale(glm::fmat4{}, glm::fvec3{radius, 0.0f, radius});

    glUniformMatrix4fv(m_shaders.at("orbit").u_locs.at("ModelMatrix"),
                       1, GL_FALSE, glm::value_ptr(model_matrix));
}

void ApplicationSolar::updateView() {
    // vertices are transformed in camera space, so camera transform must be inverted
    glm::fmat4 view_matrix = glm::inverse(m_view_transform);

    // bind new shader
    glUseProgram(m_shaders.at("planet").handle);
    // upload matrix to gpu
    glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ViewMatrix"),
                       1, GL_FALSE, glm::value_ptr(view_matrix));

    glm::fvec4 lightPos = view_matrix * glm::fvec4{0.0f, 0.0f, 0.0f, 1.0};

    glUniform3fv(m_shaders.at("planet").u_locs.at("LightPosition"),
                        1, glm::value_ptr(glm::fvec3{lightPos}));

    glUseProgram(m_shaders.at("star").handle);
    glUniformMatrix4fv(m_shaders.at("star").u_locs.at("ViewMatrix"),
                       1, GL_FALSE, glm::value_ptr(view_matrix));

    glUseProgram(m_shaders.at("orbit").handle);
    glUniformMatrix4fv(m_shaders.at("orbit").u_locs.at("ViewMatrix"),
                       1, GL_FALSE, glm::value_ptr(view_matrix));
}

void ApplicationSolar::updateProjection() {
    glUseProgram(m_shaders.at("planet").handle);
    // upload matrix to gpu
    glUniformMatrix4fv(m_shaders.at("planet").u_locs.at("ProjectionMatrix"),
                       1, GL_FALSE, glm::value_ptr(m_view_projection));

    glUseProgram(m_shaders.at("star").handle);
    glUniformMatrix4fv(m_shaders.at("star").u_locs.at("ProjectionMatrix"),
                       1, GL_FALSE, glm::value_ptr(m_view_projection));

    glUseProgram(m_shaders.at("orbit").handle);
    glUniformMatrix4fv(m_shaders.at("orbit").u_locs.at("ProjectionMatrix"),
                       1, GL_FALSE, glm::value_ptr(m_view_projection));
}

// update uniform locations
void ApplicationSolar::uploadUniforms() {
    updateUniformLocations();

    updateView();
    updateProjection();
}

// handle key input
void ApplicationSolar::keyCallback(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, -0.1f});
        updateView();
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.0f, 0.1f});
        updateView();
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{-0.1f, 0.0f, 0.0f});
        updateView();
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.1f, 0.0f, 0.0f});
        updateView();
    }
    else if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, 0.1f, 0.0f});
        updateView();
    }
    else if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS){
        m_view_transform = glm::translate(m_view_transform, glm::fvec3{0.0f, -0.1f, 0.0f});
        updateView();
    }
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS){
        //use blinn-phong shader
        shadingMode = 1;
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS){
        //use cel shader
        shadingMode = 2;
    }
}

void ApplicationSolar::mouseCallback(double xpos, double ypos){
    float mouseSpeed = 0.005f;

    float horizontalAngle = mouseSpeed * (float)(xpos);
    float verticalAngle = mouseSpeed * (float)(ypos);

    view_horizontal_angle += horizontalAngle;
    view_vertical_angle += verticalAngle;

    /*glm::fvec3 direction{(float)(cos(view_vertical_angle) * sin(view_horizontal_angle)),
                         (float)(sin(view_vertical_angle)),
                         (float)(cos(view_vertical_angle) * cos(view_horizontal_angle))};*/

    glm::fvec3 right{(float)(sin(view_horizontal_angle - M_PI/2.0f)),
                     0,
                     (float)(cos(view_horizontal_angle- M_PI/2.0f))};

    //glm::fvec3 up = glm::cross(right, direction);

    m_view_transform = glm::rotate(m_view_transform, -horizontalAngle, glm::fvec3{0.0, 1.0, 0.0});

    m_view_transform = glm::rotate(m_view_transform, verticalAngle, right);
//    m_view_transform = glm::rotate(m_view_transform, verticalAngle, glm::fvec3{1.0f, 0.0f, 0.0f});

    //m_view_transform = glm::translate(m_view_transform, view_current_translation);
    updateView();
}

GLenum ApplicationSolar::getTextureUnit(int i) const {
    switch(i) {
        case 0: return GL_TEXTURE0;
        case 1: return GL_TEXTURE1;
        case 2: return GL_TEXTURE2;
        case 3: return GL_TEXTURE3;
        case 4: return GL_TEXTURE4;
        case 5: return GL_TEXTURE5;
        case 6: return GL_TEXTURE6;
        case 7: return GL_TEXTURE7;
        case 8: return GL_TEXTURE8;
        case 9: return GL_TEXTURE9;
        case 10: return GL_TEXTURE10;
    }
}


void ApplicationSolar::initializeTextures() {
    for(int i=0; i < planets.size(); i++){
        Planet currentPlanet = planets[i];
        texture_object tex_object;

        glActiveTexture(getTextureUnit(i));
        glGenTextures(1, &tex_object.handle);
        glBindTexture(GL_TEXTURE_2D, tex_object.handle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //glTexImage2D(GL_TEXTURE_2D, 0, planets[i].texture.channels, planets[i].texture.width, planets[i].texture.height, 0, GL_RGBA, )
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     currentPlanet.texture.channels,
                     (GLsizei) currentPlanet.texture.width,
                     (GLsizei) currentPlanet.texture.height,
                     0,
                     currentPlanet.texture.channels,
                     currentPlanet.texture.channel_type,
                     currentPlanet.texture.ptr());

        tex_object.target = getTextureUnit(i);

        texture_objects.push_back(tex_object);
    }
}

// load shader programs
void ApplicationSolar::initializeShaderPrograms() {
    // store shader program objects in container
    m_shaders.emplace("planet", shader_program{m_resource_path + "shaders/simple.vert",
                                               m_resource_path + "shaders/simple.frag"});

    // request uniform locations for shader program
    m_shaders.at("planet").u_locs["NormalMatrix"] = -1;
    m_shaders.at("planet").u_locs["ModelMatrix"] = -1;
    m_shaders.at("planet").u_locs["ViewMatrix"] = -1;
    m_shaders.at("planet").u_locs["ProjectionMatrix"] = -1;
    m_shaders.at("planet").u_locs["DiffuseColor"] = -1;
    m_shaders.at("planet").u_locs["LightPosition"] = -1;
    m_shaders.at("planet").u_locs["ShadingMode"] = -1;
    m_shaders.at("planet").u_locs["ColorTex"] = -1;

    m_shaders.emplace("star", shader_program{m_resource_path + "shaders/stars.vert",
                                             m_resource_path + "shaders/stars.frag"});

    m_shaders.at("star").u_locs["ProjectionMatrix"] = -1;
    m_shaders.at("star").u_locs["ViewMatrix"] = -1;

    m_shaders.emplace("orbit", shader_program{m_resource_path + "shaders/orbit.vert",
                                              m_resource_path+"shaders/orbit.frag"});

    m_shaders.at("orbit").u_locs["ProjectionMatrix"] = -1;
    m_shaders.at("orbit").u_locs["ViewMatrix"] = -1;
    m_shaders.at("orbit").u_locs["ModelMatrix"] = -1;
}

// load models
void ApplicationSolar::initializeGeometry() {
    model planet_model = model_loader::obj(m_resource_path + "models/sphere.obj", model::NORMAL | model::TEXCOORD);

    // generate vertex array object
    glGenVertexArrays(1, &planet_object.vertex_AO);
    // bind the array for attaching buffers
    glBindVertexArray(planet_object.vertex_AO);

    // generate generic buffer
    glGenBuffers(1, &planet_object.vertex_BO);
    // bind this as an vertex array buffer containing all attributes
    glBindBuffer(GL_ARRAY_BUFFER, planet_object.vertex_BO);
    // configure currently bound array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * planet_model.data.size(), planet_model.data.data(), GL_STATIC_DRAW);

    // activate first attribute on gpu
    glEnableVertexAttribArray(0);
    // first attribute is 3 floats with no offset & stride
    glVertexAttribPointer(0, model::POSITION.components, model::POSITION.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::POSITION]);
    // activate second attribute on gpu
    glEnableVertexAttribArray(1);
    // second attribute is 3 floats with no offset & stride
    glVertexAttribPointer(1, model::NORMAL.components, model::NORMAL.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::NORMAL]);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, model::TEXCOORD.components, model::TEXCOORD.type, GL_FALSE, planet_model.vertex_bytes, planet_model.offsets[model::TEXCOORD]);


    // generate generic buffer
    glGenBuffers(1, &planet_object.element_BO);
    // bind this as an vertex array buffer containing all attributes
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planet_object.element_BO);
    // configure currently bound array buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model::INDEX.size * planet_model.indices.size(), planet_model.indices.data(), GL_STATIC_DRAW);

    // store type of primitive to draw
    planet_object.draw_mode = GL_TRIANGLES;
    // transfer number of indices to model object
    planet_object.num_elements = GLsizei(planet_model.indices.size());



    /** ASSIGNMENT 2 **/
    //stars
    glGenBuffers(1, &star_object.vertex_BO);
    glBindBuffer(GL_ARRAY_BUFFER, star_object.vertex_BO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * stars.size(), stars.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &star_object.vertex_AO);
    glBindVertexArray(star_object.vertex_AO);
    glBindBuffer(GL_ARRAY_BUFFER, star_object.vertex_BO);

    //position
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    //color
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    star_object.draw_mode = GL_POINTS;
    star_object.num_elements = GLsizei(stars.size() / 6);

    glEnable(GL_PROGRAM_POINT_SIZE);

    //orbits
    glGenBuffers(1, &orbit_object.vertex_BO);
    glBindBuffer(GL_ARRAY_BUFFER, orbit_object.vertex_BO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * orbit_vertices.size(), orbit_vertices.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &orbit_object.vertex_AO);
    glBindVertexArray(orbit_object. vertex_AO);
    glBindBuffer(GL_ARRAY_BUFFER, orbit_object.vertex_BO);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4,3,GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);

    orbit_object.draw_mode = GL_LINE_LOOP;
    orbit_object.num_elements = GLsizei(orbit_vertices.size() / 3);
}

ApplicationSolar::~ApplicationSolar() {
    glDeleteBuffers(1, &planet_object.vertex_BO);
    glDeleteBuffers(1, &planet_object.element_BO);
    glDeleteVertexArrays(1, &planet_object.vertex_AO);
}

// exe entry point
int main(int argc, char* argv[]) {
    Launcher::run<ApplicationSolar>(argc, argv);
}