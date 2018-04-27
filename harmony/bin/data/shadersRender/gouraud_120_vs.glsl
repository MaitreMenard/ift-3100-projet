// IFT3100H18 ~ gouraud_120_vs.glsl

#version 120

// attributs en sortie
varying vec3 interpolationColor;

// couleurs de réflexion du matériau
uniform vec3 colorAmbient;
uniform vec3 colorDiffuse;
uniform vec3 colorSpecular;

// facteur de brillance spéculaire du matériau
uniform float brightness;

// position d'une source de lumière
uniform vec3 lightPosition;

void main()
{
  // transformation de la normale du sommet dans l'espace de vue
  vec3 viewSpaceNormal = vec3(gl_NormalMatrix * gl_Normal);

  // transformation de la position du sommet dans l'espace de vue
  vec3 viewSpacePosition = vec3(gl_ModelViewMatrix * gl_Vertex);

  // re-normaliser la normale
  vec3 N = normalize(viewSpaceNormal);

  // calculer la direction de la surface vers la lumière (L)
  vec3 L = normalize(lightPosition - viewSpacePosition);

  // calculer le niveau de réflexion diffuse (N • L)
  float reflectionDiffuse = max(dot(N, L), 0.0);

  // réflexion spéculaire par défaut
  float reflectionSpecular = 0.0;

  // calculer la réflexion spéculaire seulement s'il y a réflexion diffuse
  if (reflectionDiffuse > 0.0)
  {
    // calculer la direction de la surface vers la caméra (V)
    vec3 V = normalize(-viewSpacePosition);

    // calculer la direction de la réflection (R) du rayon incident (-L) en fonction de la normale (N)
    vec3 R = reflect(-L, N);

    // calculer le niveau de réflexion spéculaire (R • V)
    reflectionSpecular = pow(max(dot(V, R), 0.0), brightness);
  }

  // calculer la couleur du fragment
  interpolationColor = vec3(
    colorAmbient +
    colorDiffuse * reflectionDiffuse +
    colorSpecular * reflectionSpecular);

  // transformation de la position du sommet par les matrices de modèle, vue et projection
  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
}
