#ifndef APPLICATION_SOLAR_HPP
#define APPLICATION_SOLAR_HPP

#include "application.hpp"
#include "model.hpp"
#include "structs.hpp"

#include "planet.hpp"
#include <vector>

// gpu representation of model
class ApplicationSolar : public Application {
public:
    // allocate and initialize objects
    ApplicationSolar(std::string const& resource_path);
    // free allocated objects
    ~ApplicationSolar();

    // update uniform locations and values
    void uploadUniforms();
    // update projection matrix
    void updateProjection();
    // react to key input
    void keyCallback(int key, int scancode, int action, int mods);
    // react to mouse movement
    void mouseCallback(double xpos, double ypos);
    // draw all objects
    void render() const;

protected:
    void initializeShaderPrograms();
    void initializeGeometry();
    void initializeTextures();
    void updateView();

    int getIndexOf(Planet const& planet) const;

    //render a specific planet (or moon)
    void renderPlanet(Planet const& planet, glm::fmat4& transBase) const;
    //draws the planet orbits
    void renderOrbit(float radius) const;
    //render stars
    void renderStars() const;

    // calculates and uploads the model- and normal matrix for planet
    void uploadPlanetTransforms(Planet const& planet, glm::fmat4& transBase) const;

    // calculates and uploads the modelmatrix for the orbits
    void uploadOrbitTransforms(float radius) const;

    //
    GLenum getTextureUnit(int i) const;

    float view_horizontal_angle;
    float view_vertical_angle;

    // Assign. 1
    std::vector<Planet> planets;

    // Assign. 2
    std::vector<float> stars;

    std::vector<float> orbit_vertices;

    std::vector<texture_object> texture_objects;

    //shader choice
    int shadingMode;

    // cpu representation of model
    model_object planet_object;
    model_object star_object;
    model_object orbit_object;
};

#endif