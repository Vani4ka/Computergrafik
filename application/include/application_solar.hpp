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

  //Assign. 1 
  //calculates and uploads the model- and normal matrix
  void upload_planet_transforms(Planet const& planet) const;

 protected:
  void initializeShaderPrograms();
  void initializeGeometry();
  void updateView();

  float view_horizontal_angle = 0.0f;
  float view_vertical_angle = 0.0f;

  // Assign. 1
  std::vector<Planet> planets;

  // cpu representation of model
  model_object planet_object;
};

#endif