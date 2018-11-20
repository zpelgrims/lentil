#pragma once

// returns fresnel transmittance or 0.0f
static inline float lens_pt_sample_aperture(
    const lens_t *lens,
    const float lambda, // wavelength in nm
    const float *spos, // set spos[2] = - focus sensor shift
    float *sdir,
    const float *apos,
    float *opos,
    float *odir,
    float *n)
{
  sdir[0] = apos[0] - spos[0];
  sdir[1] = apos[1] - spos[1];
  sdir[2] = lens->length - lens->aperture_pos - spos[2];
  normalise(sdir);
  float jacobian = 1.0f;
  for(int k=0;k<4;k++)
  {
    float apos2[3] = {apos[0], apos[1], apos[2]};
    // do one step of iteration on the specular manifold:
    const float transmittance = lensmf_iterate_sensor(
        lens, lambda, spos, sdir, apos2, &jacobian);
    if(transmittance <= 0.0f) return 0.0f;
    // TODO: could look at error in aperture position
    // float err = (apos[0] - apos2[0])*(apos[0] - apos2[0])+
    //             (apos[1] - apos2[1])*(apos[1] - apos2[1]);
    // fprintf(stderr, "err[%d] = %g\n", k, err);
  }
  // return transmittance * manifold jacobian determinant
  const float dist = lens_get_thickness(lens->element+lens->num-1, lens->zoom)-spos[2];
  const float G = sdir[2]*sdir[2]*sdir[2]*sdir[2] /(dist*dist);
  // XXX not sure which combination of * / and the two:
  return G / jacobian * evaluate(lens, lambda, spos, sdir, opos, odir, 0, 0, n);
}

static inline float lens_lt_sample_aperture(
    const lens_t *lens,
    const float lambda,   // wavelength in nm
    const float *scene,   // 3d point in scene in camera space
    const float *apos,    // 3d point on aperture (in camera space, z is known)
    float *spos,          // output point and direction on sensor plane/plane
    float *sdir,
    float *opos,          // output point and direction on outer pupil
    float *odir,
    float *n)
{
  odir[0] = apos[0] - scene[0];
  odir[1] = apos[1] - scene[1];
  odir[2] = scene[2];
  normalise(odir);
  for(int k=0;k<4;k++)
  {
    float apos2[3] = {apos[0], apos[1], apos[2]};
    // do one step of iteration on the specular manifold:
    const float transmittance = lensmf_iterate_scene(
        lens, lambda, scene, opos, odir, apos2);
    if(transmittance <= 0.0f)
    {
      fprintf(stderr, "ouch: o %g %g %g -- %g %g %g\n",
          opos[0], opos[1], opos[2],
          odir[0], odir[1], odir[2]);
      return 0.0f;
    }

    // TODO: could look at error in aperture position
    // float err = (apos[0] - apos2[0])*(apos[0] - apos2[0])+
    //             (apos[1] - apos2[1])*(apos[1] - apos2[1]);
    // fprintf(stderr, "err[%d] = %g\n", k, err);
  }
  // TODO: return transmittance * manifold jacobian determinant
  // TODO: so: pass in a path_t and compute derivatives, eval det Tp * G
  for(int i=0;i<3;i++) spos[i] = scene[i];
  spos[2] = -scene[2];
  for(int i=0;i<3;i++) sdir[i] = odir[i];
#if 0
  // fprintf(stderr, "starting with %g %g %g -- %g %g %g\n",
  //     spos[0], spos[1], spos[2],
  //     sdir[0], sdir[1], sdir[2]);
  // XXX TODO: make sure this round trips as expected with evaluate() re:signs of dir
  fprintf(stderr, "=======================\n");
  fprintf(stderr, "ev org %g %g %g -- %g %g %g \n",
      spos[0], spos[1], spos[2],
      sdir[0], sdir[1], sdir[2]);
  float t0 = evaluate_reverse(lens, lambda, spos, sdir, 0, 0, 0, 0, n);
  float opos2[3], odir2[3];
  float spos2[3], sdir2[3];
  for(int k=0;k<3;k++) spos2[k] = spos[k];
  for(int k=0;k<3;k++) sdir2[k] = -sdir[k];
  sdir2[2] = -sdir2[2];
  spos2[2] = 0.0;
  fprintf(stderr, "ev rev %g %g %g -- %g %g %g tr %g\n",
      spos[0], spos[1], spos[2],
      sdir[0], sdir[1], sdir[2],
      t0);
  float t1 = evaluate(lens, lambda, spos2, sdir2, opos2, odir2, 0, 0, n);
  fprintf(stderr, "ev fwd %g %g %g -- %g %g %g tr %g\n",
      opos2[0], opos2[1], opos2[2],
      odir2[0], odir2[1], odir2[2],
      t1);
  exit(666);
#endif
  return evaluate_reverse(lens, lambda, spos, sdir, 0, 0, 0, 0, n);
}
