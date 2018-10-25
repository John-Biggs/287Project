#include "RayTracer.h"
#include "IShape.h"

/**
 * @fn	RayTracer::RayTracer(const color &defa)
 * @brief	Constructs a raytracers.
 * @param	defa	The clear color.
 */

RayTracer::RayTracer(const color &defa)
	: defaultColor(defa) {
}

/**
 * @fn	void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth, const IScene &theScene) const
 * @brief	Raytrace scene
 * @param [in,out]	frameBuffer	Framebuffer.
 * @param 		  	depth	   	The current depth of recursion.
 * @param 		  	theScene   	The scene.
 */

void RayTracer::raytraceScene(FrameBuffer &frameBuffer, int depth,
	const IScene &theScene, int antiAliasing) const {
	const RaytracingCamera &camera = *theScene.camera;
	const std::vector<VisibleIShapePtr> &objs = theScene.visibleObjects;
	const std::vector<PositionalLightPtr> &lights = theScene.lights;

	for (int y = 0; y < frameBuffer.getWindowHeight(); ++y) {
		for (int x = 0; x < frameBuffer.getWindowWidth(); ++x) {
			color colorForPixel = black;
			for (int xs = 0; xs < antiAliasing; xs++) {
				for (int ys = 0; ys < antiAliasing; ys++) {
					Ray ray = camera.getRay((float)x + (float)xs / antiAliasing, (float)y + (float)ys / antiAliasing);
					colorForPixel += traceIndividualRay(ray, theScene, depth) / (float)(antiAliasing*antiAliasing);
				}
			}

			frameBuffer.setColor(x, y, colorForPixel);
		}
	}

	frameBuffer.showColorBuffer();
}


/**
 * @fn	color RayTracer::traceIndividualRay(const Ray &ray, const IScene &theScene, int recursionLevel) const
 * @brief	Trace an individual ray.
 * @param	ray			  	The ray.
 * @param	theScene	  	The scene.
 * @param	recursionLevel	The recursion level.
 * @return	The color to be displayed as a result of this ray.
 */

color RayTracer::traceIndividualRay(const Ray &ray, const IScene &theScene, int recursionLevel) const {
	HitRecord theHit = VisibleIShape::findIntersection(ray, theScene.visibleObjects);
	color result = defaultColor;
	if (glm::dot(theHit.surfaceNormal, ray.direction) > 0) {
		theHit.surfaceNormal = -theHit.surfaceNormal;
	}
	if (theHit.t < FLT_MAX) {
		for (int i = 0; i < theScene.lights.size(); i++) {
			Ray shadow = Ray(theHit.interceptPoint + EPSILON * theHit.surfaceNormal, theScene.lights[i]->lightPosition - theHit.interceptPoint);
			HitRecord shadowHit = VisibleIShape::findIntersection(shadow, theScene.visibleObjects);
			bool inShadow = shadowHit.t < theHit.t;
			color c = theScene.lights[i]->illuminate(theHit.interceptPoint, theHit.surfaceNormal, theHit.material, theScene.camera->cameraFrame, inShadow);

			if (theHit.texture != nullptr) {
				float u = glm::clamp(theHit.u, 0.0f, 1.0f);
				float v = glm::clamp(theHit.v, 0.0f, 1.0f);
				result = theHit.texture->getPixel(u, v) / 2.0f;
				result += c / 2.0f;
			}
			else {
				result += c;
			}
		}
	}
	if (recursionLevel == 0) {
		return result;
	}
	else {
		Ray reflection = Ray(theHit.interceptPoint + EPSILON + theHit.surfaceNormal,
			ray.direction - (2.0f * glm::dot(ray.direction, theHit.surfaceNormal))*theHit.surfaceNormal);
		return result + .1f*recursionLevel*traceIndividualRay(reflection, theScene, recursionLevel - 1);
	}
}
