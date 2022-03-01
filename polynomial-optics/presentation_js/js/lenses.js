var NSS = new Object();
NSS['svg']='http://www.w3.org/2000/svg';
NSS['xlink']='http://www.w3.org/1999/xlink';
NSS['xmlns']='http://www.w3.org/2000/svg';
var ROOT_NODE = document.getElementById("lensviewer");

var global_scale = 1.0;
var mousepointer = ROOT_NODE.createSVGPoint();
var aperturepointer = ROOT_NODE.createSVGPoint();

// parametrize ray input:
var ray_num = new Object();
ray_num[0] = 200;
ray_num[1] = 200;
ray_num[2] = 27;
ray_num[3] = 27;
ray_num[4] = 101;
ray_num[5] = 27;
ray_num[6] = 13;
var ray_scale = 1;
var ray_par = 0;
var ray_freeze = 0;

// lens_radius, thickness, ior, vno, housing_radius
var LENS_RADIUS=0;
var LENS_THICKNESS=1;
var LENS_IOR=2;
var LENS_VNO=3;
var LENS_HOUSING_RADIUS=4;

var lens_curr = 2;
var lensdb = new Object();
var lensdb_cnt = 0;
var lensdb_name = new Object();
lensdb_name[lensdb_cnt] = 'fisheye-ii';
lensdb[lensdb_cnt++] = [
[85.00   , 2.040, 1.62041, 60.29,  26],
[16.45   , 8.320, 1      , 1    ,  15.5],
[61.18   , 1.700, 1.81600, 46.63,  15],
[20.15   ,10.316, 1      , 1    ,  15],
[-204.00 , 3.430, 1.72000, 43.69,  10],
[-31.26  , 0.250, 1      , 1    ,  10],
[-27.00  , 2.780, 1.77250, 49.61,  9],
[11.48   , 4.930, 1.72825, 28.46,  8],
[-55.84  , 5.865, 1      , 1    ,  8],
[59.67   , 2.570, 1.51742, 52.42,  7.5],
[-14.20  , 1.410, 1.83481, 42.72,  7.5],
[-76.00  , 3.660, 1      , 1    ,  9],
[10000   , 8.776, 1      , 0    ,  9], // iris
[-1732.00, 1.490, 1.84666, 23.78,  11],
[29.90   , 4.020, 1.49700, 81.61,  10],
[-21.55  , 0.190, 1      , 1    ,  10],
[44.74   , 3.210, 1.65160, 58.54,  11],
[-44.74  ,41.100, 1      , 1    ,  11],
  ];
lensdb_name[lensdb_cnt] = 'angenieux';
lensdb[lensdb_cnt++] = [
// // simple lens, abbe 0 indicates iris
// [35.0, 20.0, 1.5, 54.0, 15.0],    // begin bk7 lens
// [-35.0, 1.73, 1.0, 100.0, 15.0],  // end lens
// [100000.0, 30.0, 1.0, 0.0, 15.0], // iris
// angenieux:
[164.13,		10.99	,			1.6751	, 32.3	,54],
[559.2,		  0.23	,			1.0   , 1.0	  ,54],
[100.12,		11.45	,			1.6689	, 46.7  ,51],
[213.54,		0.23	,		  1.0   , 1.0		,51],
[58.04 , 	  22.95	, 		1.6913	, 53.8	,41],
[2551.1,    2.58	,   	1.6751	, 32.3	,41],
[32.39 , 	  15.66	,	    1.0   , 1.0		,27],
[99999 , 	  15.00	,	    1.0   , 0.0		,25.5], // iris
[-40.42,		2.74	,			1.6992	, 30.2	,25],
[192.98,		27.92	,			1.6204	, 60.2	,36],
[-55.53,		0.23	,		  1.0   , 1.0		,36],
[192.98,		7.98	,			1.6913	, 53.8	,35],
[-225.3,		0.23	,	 	  1.0   , 1.0		,35],
[175.09,		8.48	,		  1.6913 ,	53.8	,35],
[-203.55,		55.742,	    1.0   , 1.0	,35],
];

lensdb_name[lensdb_cnt] = 'angenieux_49';
lensdb[lensdb_cnt++] = [
[80.87201769651264, 5.415118957440285, 1.6751, 32.3, 26.60749988187219],
[275.5354432211654, 0.11332824023760378, 1.0, 1.0, 26.60749988187219],
[49.33227570690822, 5.641775437915492, 1.6689, 46.7, 25.129305443990404],
[105.21788008842569, 0.11332824023760378, 1.0, 1.0, 25.129305443990404],
[28.598135058219665, 11.30818744979568, 1.6913, 53.8, 20.20199065105111],
[1257.0072768267435, 1.271247216578338, 1.6751, 32.3, 20.20199065105111],
[15.959572614330376, 7.716174965742935, 1.0, 1.0, 13.303749940936095],
[49272.65519791365, 7.3909721894089415, 1.0, 0.0, 12.564652721995202],
[-19.91620639306063, 1.3500842532653667, 1.6992, 30.2, 12.318286982348237],
[95.0873208741425, 13.757062901886512, 1.6204, 60.2, 17.738333254581462],
[-27.361379045191903, 0.11332824023760378, 1.0, 1.0, 17.738333254581462],
[95.0873208741425, 3.9319972047655574, 1.6913, 53.8, 17.245601775287533],
[-111.01240228492232, 0.11332824023760378, 1.0, 1.0, 17.245601775287533],
[86.27235470957412, 4.178362944412522, 1.6913, 53.8, 17.245601775287533],
[-100.29549261027935, 27.465838118802214, 1.0, 1.0, 17.245601775287533]

];

function handle_lens_event(evnt, action)
{
  var el = (evnt.target || evnt.srcElement);
  var svg  = ROOT_NODE;
  var pt   = svg.createSVGPoint();
  var g    = svg.querySelector('#lens_group');

  pt.x = evnt.pageX;
  pt.y = evnt.pageY;
  var h = lensdb[lens_curr][0][LENS_HOUSING_RADIUS];
  var box = svg.getBoundingClientRect();
  var m = pt;
  // manually undo bloody transform:
  m.x = -(1000*(pt.x - box.left)/box.width  - 500)/global_scale;
  m.y =  ( 400*(pt.y - box.top )/box.height - 200)/global_scale;

  var pos = [0.0, -2500, -9999];
  // var pos = [0.0, 2300, -9999];


  // console.log("x = "+m.x+" y = "+m.y);
  if(m.x > 20)
  {
    var off = 0;
    for(var i=0;i<lensdb[lens_curr].length;i++)
    {
      if(lensdb[lens_curr][i][LENS_IOR] == 1.0 &&
         lensdb[lens_curr][i][LENS_VNO] == 0.0)
      {
        if(evnt.button == 1)
        { // adjust iris size:
          lensdb[lens_curr][i][LENS_HOUSING_RADIUS] = m.y;
          g.removeChild(g.querySelector('#iris'));
          var d  = 'M' + off + ' ' + m.y;
          d += 'L' + off + ' ' + (-m.y);
          add_lens(d, g, 1.0, 0.0);
        }
        break;
      }
      off += lensdb[lens_curr][i][LENS_THICKNESS];
    }
    if(evnt.button == 0)
    { // sample aperture for lt
      aperturepointer.x = off;
      aperturepointer.y = m.y;
      target = g.querySelector('#lens_aperture');
      target.setAttribute('cx', off);
      target.setAttribute('cy', m.y);
      target.setAttribute('r', 1);
      out = [0,0,0,0,0];
      sensor = [0,0,0,0,0.55];
      
      // why does second one not work?
      // error = lt_aperture_sample_fisheye_ii(lensdb[lens_curr], 0.0, m.y, 0.0, mousepointer.y, -mousepointer.x, sensor, out, 0);
      // error = lt_aperture_sample_angenieux(lensdb[lens_curr], 0.0, m.y,  0.0, mousepointer.y, -mousepointer.x, sensor, out, 0);
      error = lt_aperture_sample_angenieux_writeout(lensdb[lens_curr], 0.0, m.y,  0.0, mousepointer.y, -mousepointer.x, sensor, out, 0);
      
      // opp = [0,0,0,0,0,0];
      // error = raytrace_from_sensor(lensdb[lens_curr], sensor, opp);
    }
  }
  else
  {
    mousepointer = m;
    set_ray('', 666, 1); // clear aperture sampling ray
    set_ray('',1337,1); // and error vectors
    set_ray('',1338,1);
    set_ray('',2337,1); // and error vectors
    set_ray('',2338,1);
  }

  target = g.querySelector('#lens_target');
  target.setAttribute('cx', mousepointer.x);
  target.setAttribute('cy', mousepointer.y);
  target.setAttribute('r', 1);
  // (re-)raytrace
  m = mousepointer;
  m.x = pos[2];
  m.y = pos[1];
  for(var i=0;i<ray_num[lens_curr];i++)
  {
    var o = (i-((ray_num[lens_curr]-1.0)/2.0))/(ray_num[lens_curr]-1.0) * 2.0 * h * ray_scale;
    if(ray_par)
    {
      var inp = [0.0, o, 0.0, m.y/m.x];
      raytrace(lensdb[lens_curr], inp, i, m.x, m.y+o);
    }
    else
    {
      var inp = [0.0, o, 0.0, (m.y-o)/m.x];
      raytrace(lensdb[lens_curr], inp, i, m.x, m.y);
    }
  }
  return false;
}

function add_lens(pathd, g, ior, vno)
{
  var path = document.createElementNS(NSS['svg'], 'path');
  path.setAttribute('stroke', '#000000');
  path.setAttribute('stroke-width', .8/global_scale);
  // path.setAttribute('fill', 'rgba(100, 100, 150, '+((ior-1.5)*4)+')');
  path.setAttribute('fill', 'rgba(0, 100, 200, .5)');
  if(ior == 1.0 && vno == 0.0)
    path.setAttribute('id', 'iris');
  else
    path.setAttribute('id', 'lens ' + Date());
  path.setAttribute('d', pathd);
  g.appendChild(path);
}

function add_ray(i, g)
{
  var path = document.createElementNS(NSS['svg'], 'path');
  path.setAttribute('stroke', '#000000');
  path.setAttribute('stroke-width', .8/global_scale);
  path.setAttribute('fill', 'none');
  path.setAttribute('id', 'lens_ray' + i);
  path.setAttribute('d', 'M0 0, L0 0');
  g.appendChild(path);
}

function add_box(lenses, g)
{
  var rect = document.createElementNS(NSS['svg'], 'rect');
  rect.setAttribute('stroke', 'rgba(0, 0, 0, .2)');
  rect.setAttribute('fill', 'none');
  rect.setAttribute('id', 'lens_box');
  var t = 0;
  for(var i=0;i<lenses.length;i++)
    t += lenses[i][LENS_THICKNESS];
  var h = lenses[0][LENS_HOUSING_RADIUS];
  rect.setAttribute('x', 0);
  rect.setAttribute('y', -h);
  rect.setAttribute('width', t);
  rect.setAttribute('height', 2*h);
  g.appendChild(rect);
  // optical axis:
  var path = document.createElementNS(NSS['svg'], 'path');
  path.setAttribute('stroke', '#000000');
  path.setAttribute('fill', 'none');
  path.setAttribute('id', 'lens_optical_axis' + i);
  path.setAttribute('d', 'M-50 0, L'+(t+50)+' 0');
  g.appendChild(path);

  // while we have all the bounds, scale to fit viewport 1000x400
  var sx = 400.0/t;
  var sy = 350.0/h;
  var s = Math.min(sx, sy);
  global_scale = s;
  path.setAttribute('stroke-width', 1.0/global_scale);
  rect.setAttribute('stroke-width', .5/global_scale);
  g.setAttribute('transform', 'matrix('+(-s)+',0,0,'+s+',500,200)');
}

function lens_init(num)
{
  if(num >= 0)//== slide_num_lens) // slide number, which is number after the # minus one in ff
  {
    // var svg = document.createElementNS(NSS['xmlns'], 'svg');
    // svg.setAttribute('id', 'lensview_svg');
    // svg.setAttribute('width', '100%');
    // svg.setAttribute('height', '100%');
    var g = document.createElementNS(NSS['svg'], 'g');
    g.setAttribute('id', 'lens_group');
    g.setAttribute('shape-rendering', 'inherit');
    g.setAttribute('pointer-events', 'all');

    add_box(lensdb[lens_curr], g);
    draw_lens(lensdb[lens_curr], g);
    var rm = 0;
    for(var i=0;i<lensdb_cnt;i++)
      rm = Math.max(rm, ray_num[i]);
    for(var i=0;i<rm;i++)
      add_ray(i, g);
    add_ray(666, g); // aperture sampling ray

    // add user chosen points
    var c0 = document.createElementNS(NSS['svg'], 'circle');
    c0.setAttribute('stroke', '#000000');
    c0.setAttribute('stroke-width', .8/global_scale);
    c0.setAttribute('fill', 'none');
    c0.setAttribute('id', 'lens_target');
    c0.setAttribute('cx', '0');
    c0.setAttribute('cy', '0');
    c0.setAttribute('r', '0');
    g.appendChild(c0);
    var c1 = document.createElementNS(NSS['svg'], 'circle');
    c1.setAttribute('stroke', '#000000');
    c1.setAttribute('stroke-width', .8/global_scale);
    c1.setAttribute('fill', 'none');
    c1.setAttribute('id', 'lens_aperture');
    c1.setAttribute('cx', '0');
    c1.setAttribute('cy', '0');
    c1.setAttribute('r', '0');
    g.appendChild(c1);

    // add indicators for newton iteration:
    add_ray(1337, g);
    add_ray(1338, g);
    add_ray(2337, g);
    add_ray(2338, g);

    // svg.appendChild(g);
    ROOT_NODE.appendChild(g);
  }
  else
  {
    // else delete that stuff again.
    var g = ROOT_NODE.querySelector('#lens_group');
    if(g)
      ROOT_NODE.removeChild(g);
  }
}


function set_ray(pathd, num, error)
{
  var path = document.getElementById('lens_ray'+num);
  if(!path) return;
  if(error)
  {
    path.setAttribute('stroke', '#ff0000');
    path.setAttribute('d', 'M0 0, L0 0');
  }
  else
  {
    path.setAttribute('d', pathd);
    if(num == 666)
    { // optimised aperture ray
      path.setAttribute('stroke-width', 1./global_scale);
      path.setAttribute('stroke', 'rgba(255, 100, 0, 1.0)');
    }
    else if(num > 2000)
    { // update deltas
      path.setAttribute('stroke-width', 3./global_scale);
      path.setAttribute('stroke', 'rgba(0, 255, 20, 1.0)');
    }
    else if(num > 1000)
    { // error deltas
      path.setAttribute('stroke-width', 3./global_scale);
      path.setAttribute('stroke', 'rgba(255, 20, 0, 1.0)');
    }
    else
      path.setAttribute('stroke', 'rgba(255, 100, 0, 0.5)');
  }
}

function draw_lens(lenses, g)
{
  var d = '';
  var off = 0;
  for(var i=0;i<lenses.length-1;i++)
  {
    var t = lenses[i][LENS_THICKNESS];
    var h = lenses[i][LENS_HOUSING_RADIUS];
    if(lenses[i][LENS_IOR] > 1.0)
    {
      var h2 = lenses[i+1][LENS_HOUSING_RADIUS];
      var r = lenses[i][LENS_RADIUS];
      var r2 = lenses[i+1][LENS_RADIUS];
      with(Math)
      {
        var z = Math.abs(r) - Math.sqrt(Math.max(0.0, r*r - h*h));
        var z2 = Math.abs(r2) - Math.sqrt(Math.max(0.0, r2*r2 - h2*h2));
      }
      if(r < 0) z = - z;
      if(r2 < 0) z2 = - z2;
      // start point s = (off+z, h), end will be e = (off+z, -h)
      d = 'M' + (off+z) +' '+h;
      // now curve (t1, t2, e) to top, following lens. we'd like to intersect the optical axis at (off, 0),
      // that means (((s+t1)/2 + (t1+t2)/2)/2 + ((e+t2)/2 + (t1+t2)/2)/2)/2 = (off, 0) or
      // (s+t1)/8 + (t1+t2)/4 + (e+t2)/8 = (off, 0) or
      // s/8 + e/8 + t1 3/8 + t2 3/8 = (off, 0)
      // or for just z:
      // z/8 + z/8 + tz 3/8 + tz 3/8 = 0
      // z/4 + tz 3/4 = 0 => tz = -z/3
      var tz = -z/3.0;
      var tz2 = -z2/3.0;
      // to find the distance to the optical axis, we make the tangents tangent to the sphere:
      // ((tz,th) - (z, h)).(r-z,h) = 0
      // (tz - z)*(r-z) + (th - h)*h = 0
      var th = h + ((tz - z)*(r-z))/h;
      var th2 = h2 + ((tz2 - z2)*(r2-z2))/h2;
      d += ' C' + (off+tz)    + ' ' + th     + ',' + (off+tz)    + ' ' + (-th) + ',' + (off+z) + ' ' + (-h);
      d += ' L' + (off+t+z2)  + ' ' + (-h2);
      d += ' C' + (off+t+tz2) + ' ' + (-th2) + ',' + (off+t+tz2) + ' ' + th2 + ',' + (off+z2+t) + ' ' + h2;
      d += ' Z';
      add_lens(d, g, lenses[i][LENS_IOR], lenses[i][LENS_VNO]);
    }
    else if(lenses[i][LENS_VNO] == 0.0)
    {
      // iris
      d  = 'M' + off + ' ' + h;
      d += 'L' + off + ' ' + (-h);
      add_lens(d, g, 1.0, 0.0);
    }
    off += t;
  }
}

function raytrace(lenses, inp, num, mx, my)
{
  var error = 0;
  var n1 = 1.0;
  var dim_up = 1;
  var pos = [inp[0], inp[1], 0.0];
  var dir = [inp[2], inp[3], 1.0];

  var d = 'M'+mx + ' ' + my;

  for(var k=0;k<lenses.length;k++)
  {
    var R = lenses[k][LENS_RADIUS];
    var t = 0.0;
    var dist = lenses[k][LENS_THICKNESS];

    // first now transmit through the medium.
    var discr = R*R - 2.0*R*(dir[1]*pos[1] + dir[0]*pos[0]) + pos[1]*pos[1]*(-dir[0]*dir[0]-1.0) + 2.0*dir[0]*dir[1]*pos[0]*pos[1] + (-dir[1]*dir[1] - 1.0)*pos[0]*pos[0];
    if(discr < 0.0) error |= 4; // fatal
    if(R > 0.0)
      t = - (Math.sqrt(discr) - R + dir[1]*pos[1] + dir[0]*pos[0])/(dir[1]*dir[1] + dir[0]*dir[0] + 1.0);
    else if(R < 0.0)
      t = - ( - Math.sqrt(discr) - R + dir[1]*pos[1] + dir[0]*pos[0])/(dir[1]*dir[1] + dir[0]*dir[0] + 1.0);

    for(var i=0;i<3;i++) pos[i] += dir[i] * t;
    // mark this ray as theoretically dead:
    if(pos[0]*pos[0] + pos[1]*pos[1] > lenses[k][LENS_HOUSING_RADIUS]*lenses[k][LENS_HOUSING_RADIUS]) error |= 16;

    d += ' L' + pos[2] + ' ' + pos[dim_up];

    // index of refraction and ratio current/next:
    // TODO: this does not depend on wavelength as it is!
    var n2 = lenses[k][LENS_IOR];
    var eta = n1/n2;

    // get normal pointing from center of intersected sphere to intersection point:
    var n = [pos[0]/R, pos[1]/R, (t-R)/R];

    var norm = Math.sqrt(dir[0]*dir[0] + dir[1]*dir[1] + dir[2]*dir[2]);
    var cos1 = - (n[0]*dir[0] + n[1]*dir[1] + n[2]*dir[2])/norm;
    var cos2_2 = 1.0-eta*eta*(1.0-cos1*cos1);
    // total (inner) reflection?
    if(cos2_2 < 0.0)
      error |= 8; // fatal
    var cos2 = Math.sqrt(cos2_2);

    if(n2 != n1)
      for(var i=0;i<3;i++) dir[i] = dir[i]*eta/norm + (eta*cos1-cos2)*n[i];
    // mark this ray as theoretically dead:
    if(dir[2] <= 0.0) error |= 2; // fatal
    // and renormalise:
    dir[0] /= dir[2];
    dir[1] /= dir[2];
    dir[2] = 1.0;

    // move to next interface:
    for(var i=0;i<3;i++) pos[i] += dir[i] * (dist-t);

    n1 = n2;
  }
  // shoot on a little more to see focus:
  for(var i=0;i<3;i++) pos[i] += dir[i]*30;

  d += ' L' + pos[2] + ' ' + pos[dim_up];

  set_ray(d, num, error);
  return error;
}

function lens_ipow(x, exp)
{
  if(exp == 0) return 1.0;
  if(exp == 1) return x;
  if(exp == 2) return x*x;
  var p2 = lens_ipow(x, exp/2);
  if(exp &  1) return x * p2 * p2;
  return p2 * p2;
}

function lens_sphereToCs(
    inp,  // spherical parameters, 2 + 2 floats
    out,  // camera space 3 + 3 floats
    sphereCenter, sphereRad)
{
  normal =
  [
    inp[0]/sphereRad,
    inp[1]/sphereRad,
    Math.sqrt(Math.max(0, sphereRad*sphereRad-inp[0]*inp[0]-inp[1]*inp[1]))/Math.abs(sphereRad)
  ];
  tempDir = [inp[2], inp[3], Math.sqrt(Math.max(0.0, 1.0-inp[2]*inp[2]-inp[3]*inp[3]))];

  ex = [normal[2], 0, -normal[0]];
  ilen = 1.0/Math.sqrt(ex[0]*ex[0]+ex[1]*ex[1]+ex[2]*ex[2]);
  for(var i=0;i<3;i++) ex[i] *= ilen;
  var ey = [0,0,0];
  ey[0] = normal[1]*ex[2] - ex[1]*normal[2];
  ey[1] = normal[2]*ex[0] - ex[2]*normal[0];
  ey[2] = normal[0]*ex[1] - ex[0]*normal[1];

  out[3] = tempDir[0] * ex[0] + tempDir[1] * ey[0] + tempDir[2] * normal[0];
  out[4] = tempDir[0] * ex[1] + tempDir[1] * ey[1] + tempDir[2] * normal[1];
  out[5] = tempDir[0] * ex[2] + tempDir[1] * ey[2] + tempDir[2] * normal[2];
  out[0] = inp[0];
  out[1] = inp[1];
  out[2] = normal[2] * sphereRad + sphereCenter;
}

function lens_csToSphere(
    inp,  // camera space 3 + 3 floats
    outp, // spherical parameters, 2 + 2 floats
    sphereCenter, sphereRad)
{
  normal =
  [
    inp[0]/sphereRad,
    inp[1]/sphereRad,
    Math.abs((inp[2]-sphereCenter)/sphereRad)
  ];
  tempDir = [inp[3], inp[4], inp[5]];
  ilen = 1.0/Math.sqrt(tempDir[0]*tempDir[0]+tempDir[1]*tempDir[1]+tempDir[2]*tempDir[2]);
  for(var i=0;i<3;i++) tempDir[i] *= ilen;

  ex = [normal[2], 0, -normal[0]];
  ilen = 1.0/Math.sqrt(ex[0]*ex[0]+ex[1]*ex[1]+ex[2]*ex[2]);
  for(var i=0;i<3;i++) ex[i] *= ilen;
  ey = [0,0,0];
  ey[0] = normal[1]*ex[2] - ex[1]*normal[2];
  ey[1] = normal[2]*ex[0] - ex[2]*normal[0];
  ey[2] = normal[0]*ex[1] - ex[0]*normal[1];
  outp[2] = tempDir[0]*ex[0]+tempDir[1]*ex[1]+tempDir[2]*ex[2];
  outp[3] = tempDir[0]*ey[0]+tempDir[1]*ey[1]+tempDir[2]*ey[2];
  outp[0] = inp[0];
  outp[1] = inp[1];
}

function lens_planeToCs(
    inp,    // plane/plane sensor space 2+2 floats
    outpos, // 3d camera space position (output)
    outdir, // 3d camera space direction (output)
    planepos)
{
  outpos[0] = inp[0];
  outpos[1] = inp[1];
  outpos[2] = planepos;

  outdir[0] = inp[2];
  outdir[1] = inp[3];
  outdir[2] = 1;

  ilen = 1.0/Math.sqrt(outdir[0]*outdir[0] + outdir[1]*outdir[1] + outdir[2]*outdir[2]);
  for(var k=0;k<3;k++) outdir[k] *= ilen;
}

function lens_spherical(pos, dir, R, center, housing_rad, normal)
{
  scv = [pos[0], pos[1], pos[2] - center];
  a = dir[0]*dir[0] + dir[1]*dir[1] + dir[2]*dir[2];
  b = 2 * (dir[0]*scv[0] + dir[1]*scv[1] + dir[2]*scv[2]);
  c = (scv[0]*scv[0]+scv[1]*scv[1]+scv[2]*scv[2]) - R*R;
  discr = b*b-4*a*c;
  if(discr < 0.0) return -1;
  t = 0.0;
  t0 = (-b-Math.sqrt(discr))/(2*a);
  t1 = (-b+Math.sqrt(discr))/(2*a);
  if(t0 < -1e-4) t = t1;
  else t = Math.min(t0, t1);
  if(t < -1e-4) return -1;

  for(var i=0;i<3;i++) pos[i] += dir[i] * t;
  if(pos[0]*pos[0] + pos[1]*pos[1] > housing_rad*housing_rad) return -1;

  normal[0] = pos[0]/R;
  normal[1] = pos[1]/R;
  normal[2] = (pos[2] - center)/R;

  return t;
}

function lens_refract(n1, n2, n, dir)
{
  if(n1 == n2)
    return 1;
  eta = n1/n2;

  norm = Math.sqrt(dir[0]*dir[0]+dir[1]*dir[1]+dir[2]*dir[2]);
  cos1 = - (n[0]*dir[0]+n[1]*dir[1]+n[2]*dir[2])/norm;
  cos2_2 = 1.0-eta*eta*(1.0-cos1*cos1);
  // total (inner) reflection?
  if(cos2_2 < 0.0)
    return 0;
  cos2 = Math.sqrt(cos2_2);
  for(var i=0;i<3;i++) dir[i] = dir[i]*eta/norm + (eta*cos1-cos2)*n[i];
  return .5;//1.0-fresnel(n1, n2, cos1, cos2);
}

// evalute sensor to outer pupil
function raytrace_from_sensor(lenses, inp, out)
{
  n1 = lenses[lenses.length-1][LENS_IOR];
  pos = [0,0,0];
  dir = [0,0,0];
  dim_up = 1;
  lens_length=0;
  for(var i=0;i<lenses.length;i++)
    lens_length+=lenses[i][LENS_THICKNESS];

  lens_planeToCs(inp, pos, dir, 0);
  var d = 'M'+(lens_length-pos[2]) + ' ' + (pos[dim_up]);
  var distsum = 0;

  for(var k=lenses.length-1;k>=0;k--)
  {
    // propagate the ray reverse to the plane of intersection optical axis/lens element:
    R = -lenses[k][LENS_RADIUS]; // negative, we're the adjoint case
    dist = lenses[k][LENS_THICKNESS];
    distsum += dist;

    //normal at intersection
    n = [0,0,0];

    t = lens_spherical(pos, dir, R, distsum + R, lenses[k][LENS_HOUSING_RADIUS], n);
    if(t < 0)
    {
      set_ray(d, 666, 0);
      return 1;
    }

    d += ' L' + (lens_length-pos[2]) + ' ' + (pos[dim_up]);

    // index of refraction and ratio current/next:
    n2 = k ? lenses[k-1][LENS_IOR] : 1.0; // outside the lens there is vacuum

    fresnel = lens_refract(n1, n2, n, dir);
    if(fresnel == 0)
    {
      set_ray(d, 666, 0);
      return 1;
    }
    ilen = 1.0/Math.sqrt(dir[0]*dir[0] + dir[1]*dir[1] + dir[2]*dir[2]);
    for(var i=0;i<3;i++) dir[i] *= ilen;

    n1 = n2;
  }
  // return [x,y,dx,dy,lambda]
  // posdir = [pos[0],pos[1],pos[2],dir[0],dir[1],dir[2]];
  // lens_csToSphere(posdir, out, distsum-Math.abs(lenses[0][LENS_RADIUS]), lenses[0][LENS_RADIUS]);
  d += ' L' + (lens_length - pos[2] - dir[2]*250)+' ' + (pos[dim_up] + dir[dim_up]*250);
  set_ray(d, 666, 0);
  out[0] = pos[0];
  out[1] = pos[1];
  out[2] = pos[2];
  out[3] = dir[0];
  out[4] = dir[1];
  out[5] = dir[2];
  return 0;
}

function lt_aperture_sample_fisheye_ii(lenses, ap_x, ap_y, scene_x, scene_y, scene_z, sensor, out, k)
{
  // kill old runs in timeouts:
  if(ap_x != 0.0 || ap_y != aperturepointer.y) return 0;
  if(scene_x != 0.0 || scene_y != mousepointer.y || scene_z != -mousepointer.x) return 0;
  // visualise progress:
  opp = [0,0,0,0,0,0];
  raytrace_from_sensor(lenses, sensor, opp);
  var lens_outer_pupil_curvature_radius = lensdb[lens_curr][0][LENS_RADIUS];
  var lens_outer_pupil_radius = lensdb[lens_curr][0][LENS_HOUSING_RADIUS];
  var error = 0;

  var eps = 1e-8;
  var sqr_err = 1e30, sqr_ap_err = 1e30;
  var prev_sqr_err = 1e32, prev_sqr_ap_err = 1e32;
  for(;k<300&&(sqr_err>eps||sqr_ap_err>eps)&&error==0;k++)
  {
    prev_sqr_err = sqr_err, prev_sqr_ap_err = sqr_ap_err;
    var begin_x = sensor[0];
    var begin_y = sensor[1];
    var begin_dx = sensor[2];
    var begin_dy = sensor[3];
    var begin_lambda = sensor[4];
    var pred_ap = [
       + -7.49341e-05  + 31.8705 *begin_dx + 0.436491 *begin_x + -0.00434863 *begin_dx*begin_dy + -9.46011e-05 *begin_x*begin_dx + 23.493 *begin_dx*lens_ipow(begin_dy, 2) + 23.4023 *lens_ipow(begin_dx, 3) + 1.65118 *begin_y*begin_dx*begin_dy + 0.0146014 *lens_ipow(begin_y, 2)*begin_dx + 0.362828 *begin_x*lens_ipow(begin_dy, 2) + 2.00488 *begin_x*lens_ipow(begin_dx, 2) + 0.017448 *begin_x*begin_y*begin_dy + -4.84545e-05 *begin_x*lens_ipow(begin_y, 2) + 0.0317825 *lens_ipow(begin_x, 2)*begin_dx + -5.88879e-05 *lens_ipow(begin_x, 3) + -0.275449 *begin_dx*lens_ipow(begin_lambda, 3) + -0.00911589 *begin_x*lens_ipow(begin_lambda, 4) + 8.4631e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.000162526 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + -0.00500642 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3) + 0.00346072 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + 1.87854e-06 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 2) + -1.10054e-09 *begin_x*lens_ipow(begin_y, 6) + -2.96149e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 3.60493e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -5.47423e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + 0.154317 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 3) + -1.629e-10 *lens_ipow(begin_y, 8)*begin_dx + -15.1635 *begin_x*lens_ipow(begin_dy, 8) + 5.78753e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_dx*begin_dy + -0.0318519 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 6) + -2.10977e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6) + 7.17351e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 1.90932e-08 *lens_ipow(begin_x, 7)*lens_ipow(begin_dx, 2) + -23795.1 *lens_ipow(begin_dx, 9)*lens_ipow(begin_dy, 2) + 1.04466e-05 *begin_x*lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + 0.15527 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + 3.65737e-05 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 4) + 5.3816e-10 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dx*begin_dy + -2.46274e-14 *lens_ipow(begin_x, 11),
       + 6.21186e-05  + 31.8523 *begin_dy + 0.436577 *begin_y + -1.05941e-05 *begin_x + 23.7694 *lens_ipow(begin_dy, 3) + 23.3543 *lens_ipow(begin_dx, 2)*begin_dy + 2.01849 *begin_y*lens_ipow(begin_dy, 2) + 0.361427 *begin_y*lens_ipow(begin_dx, 2) + 0.0319743 *lens_ipow(begin_y, 2)*begin_dy + -6.28846e-05 *lens_ipow(begin_y, 3) + 1.6358 *begin_x*begin_dx*begin_dy + 0.0172154 *begin_x*begin_y*begin_dx + 0.0144248 *lens_ipow(begin_x, 2)*begin_dy + -6.19602e-05 *lens_ipow(begin_x, 2)*begin_y + -0.000223487 *begin_x*begin_y*begin_dx*begin_dy + -0.357426 *begin_dy*lens_ipow(begin_lambda, 4) + -0.00803068 *begin_y*lens_ipow(begin_lambda, 4) + -0.0718989 *begin_y*lens_ipow(begin_dx, 4) + 0.000210128 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 0.0173154 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + 0.00024912 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 8.4255 *begin_x*begin_dx*lens_ipow(begin_dy, 5) + 9.6178e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 2) + -0.00397207 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3)*begin_dy + -0.000161052 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 3) + -0.0549936 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 6) + 2.40039e-08 *lens_ipow(begin_y, 7)*lens_ipow(begin_dy, 2) + 0.860139 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 7) + 0.0082252 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -5.87248e-11 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 5) + -1.57324e-10 *lens_ipow(begin_x, 8)*begin_dy + -6.14131e-12 *lens_ipow(begin_x, 8)*begin_y + 0.159107 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 5) + -3.2762e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy*lens_ipow(begin_lambda, 3) + 283.098 *begin_y*lens_ipow(begin_dy, 10) + -2.53306e-14 *lens_ipow(begin_y, 11) + 0.0521709 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 6) + 1.02786e-07 *begin_x*lens_ipow(begin_y, 6)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -8.88798e-14 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 9) + 1.50516e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4)*begin_dx*begin_dy
    ];
    delta_ap = [ap_x - pred_ap[0], ap_y - pred_ap[1]];
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    var dx1_domega0 = [[0,0],[0,0]];
    dx1_domega0[0][0] =  + 31.8705  + -0.00434863 *begin_dy + -9.46011e-05 *begin_x + 23.493 *lens_ipow(begin_dy, 2) + 70.207 *lens_ipow(begin_dx, 2) + 1.65118 *begin_y*begin_dy + 0.0146014 *lens_ipow(begin_y, 2) + 4.00976 *begin_x*begin_dx + 0.0317825 *lens_ipow(begin_x, 2) + -0.275449 *lens_ipow(begin_lambda, 3) + 8.4631e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.00500642 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + 3.75708e-06 *begin_x*lens_ipow(begin_y, 4)*begin_dx + -2.96149e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 2) + 0.308634 *begin_x*begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 3) + -1.629e-10 *lens_ipow(begin_y, 8) + 5.78753e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_dy + -0.191111 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 5) + 1.4347e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*begin_dx + 3.81863e-08 *lens_ipow(begin_x, 7)*begin_dx + -214156 *lens_ipow(begin_dx, 8)*lens_ipow(begin_dy, 2) + 0.776349 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2) + 3.65737e-05 *lens_ipow(begin_x, 4)*begin_y*begin_dy*lens_ipow(begin_lambda, 4) + 5.3816e-10 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dy;
    dx1_domega0[0][1] =  + -0.00434863 *begin_dx + 46.986 *begin_dx*begin_dy + 1.65118 *begin_y*begin_dx + 0.725656 *begin_x*begin_dy + 0.017448 *begin_x*begin_y + 8.4631e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 0.000325052 *lens_ipow(begin_x, 3)*begin_dy + -0.0150193 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + 0.0138429 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + 7.20986e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy + 0.154317 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 3) + -121.308 *begin_x*lens_ipow(begin_dy, 7) + 5.78753e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*begin_dx + -47590.1 *lens_ipow(begin_dx, 9)*begin_dy + 2.08933e-05 *begin_x*lens_ipow(begin_y, 4)*begin_dy*lens_ipow(begin_lambda, 4) + 0.31054 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5)*begin_dy + 3.65737e-05 *lens_ipow(begin_x, 4)*begin_y*begin_dx*lens_ipow(begin_lambda, 4) + 5.3816e-10 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dx;
    dx1_domega0[1][0] =  + 46.7086 *begin_dx*begin_dy + 0.722854 *begin_y*begin_dx + 1.6358 *begin_x*begin_dy + 0.0172154 *begin_x*begin_y + -0.000223487 *begin_x*begin_y*begin_dy + -0.287596 *begin_y*lens_ipow(begin_dx, 3) + 0.000420255 *lens_ipow(begin_y, 3)*begin_dx + 0.0173154 *begin_x*begin_y*lens_ipow(begin_dy, 2) + 0.00024912 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 8.4255 *begin_x*lens_ipow(begin_dy, 5) + -0.0119162 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_dy + -0.000483157 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 2) + 0.0164504 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + 0.159107 *begin_x*begin_y*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 5) + 0.0521709 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 6) + 1.02786e-07 *begin_x*lens_ipow(begin_y, 6)*begin_dy*lens_ipow(begin_lambda, 2) + 1.50516e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4)*begin_dy;
    dx1_domega0[1][1] =  + 31.8523  + 71.3082 *lens_ipow(begin_dy, 2) + 23.3543 *lens_ipow(begin_dx, 2) + 4.03698 *begin_y*begin_dy + 0.0319743 *lens_ipow(begin_y, 2) + 1.6358 *begin_x*begin_dx + 0.0144248 *lens_ipow(begin_x, 2) + -0.000223487 *begin_x*begin_y*begin_dx + -0.357426 *lens_ipow(begin_lambda, 4) + 0.0346308 *begin_x*begin_y*begin_dx*begin_dy + 0.00024912 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 42.1275 *begin_x*begin_dx*lens_ipow(begin_dy, 4) + 1.92356e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + -0.00397207 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + -0.329962 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 5) + 4.80079e-08 *lens_ipow(begin_y, 7)*begin_dy + 6.02097 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 6) + 0.0246756 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -1.57324e-10 *lens_ipow(begin_x, 8) + 0.318214 *begin_x*begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 5) + -3.2762e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3) + 2830.98 *begin_y*lens_ipow(begin_dy, 9) + 0.313025 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 5) + 1.02786e-07 *begin_x*lens_ipow(begin_y, 6)*begin_dx*lens_ipow(begin_lambda, 2) + 1.50516e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4)*begin_dx;
    invApJ = [[0,0],[0,0]];
    var invdetap = 1.0/(dx1_domega0[0][0]*dx1_domega0[1][1] - dx1_domega0[0][1]*dx1_domega0[1][0]);
    invApJ[0][0] =  dx1_domega0[1][1]*invdetap;
    invApJ[1][1] =  dx1_domega0[0][0]*invdetap;
    invApJ[0][1] = -dx1_domega0[0][1]*invdetap;
    invApJ[1][0] = -dx1_domega0[1][0]*invdetap;
    for(var i=0;i<2;i++)
    {
      sensor[2] += invApJ[0][i]*delta_ap[i];
      sensor[3] += invApJ[1][i]*delta_ap[i];
    }
    out[0] =  + -0.000784894  + 7.63571 *begin_dx + -1.44172 *begin_x + -0.0134346 *begin_dx*begin_dy + 8.22272e-06 *lens_ipow(begin_y, 2) + 1.89902e-05 *lens_ipow(begin_x, 2) + 12.3921 *begin_dx*lens_ipow(begin_dy, 2) + 12.7748 *lens_ipow(begin_dx, 3) + 1.158 *begin_y*begin_dx*begin_dy + 0.034187 *lens_ipow(begin_y, 2)*begin_dx + 0.722514 *begin_x*lens_ipow(begin_dy, 2) + 1.889 *begin_x*lens_ipow(begin_dx, 2) + 0.0499711 *begin_x*begin_y*begin_dy + -0.000556662 *begin_x*lens_ipow(begin_y, 2) + 0.0866542 *lens_ipow(begin_x, 2)*begin_dx + -0.000546434 *lens_ipow(begin_x, 3) + -0.267534 *begin_x*lens_ipow(begin_lambda, 3) + 3.08165e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx + -4.62769 *begin_dx*lens_ipow(begin_lambda, 6) + -9.99271e-06 *lens_ipow(begin_y, 5)*begin_dx*begin_dy + -0.116833 *begin_x*begin_y*lens_ipow(begin_dy, 5) + -1.45839 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -1.4961 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy + -0.0267323 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_lambda, 4) + -2.61715e-05 *lens_ipow(begin_x, 4)*begin_y*begin_dx*begin_dy + 3.54239e-07 *begin_x*lens_ipow(begin_y, 5)*begin_dy*begin_lambda + 0.00533347 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 5) + 0.0379735 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -0.00684859 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 4) + -3522.99 *lens_ipow(begin_dx, 9)*begin_lambda + -0.0655694 *begin_x*begin_y*begin_dy*lens_ipow(begin_lambda, 7) + -6.10333e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_lambda + -4.19322e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3) + -1.44354e-07 *lens_ipow(begin_x, 7)*lens_ipow(begin_dx, 2)*begin_lambda + -1.37455e-11 *lens_ipow(begin_x, 9)*begin_lambda + 1.17809 *begin_x*lens_ipow(begin_lambda, 10) + -17.5351 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 6) + 0.00703591 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 4) + 9.75689e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3) + 5.04947e-07 *lens_ipow(begin_x, 7)*lens_ipow(begin_dy, 4);
    out[1] =  + 0.000310766  + 7.88257 *begin_dy + -1.4375 *begin_y + 0.000527768 *begin_y*begin_dy + 1.24757e-05 *begin_x*begin_y + 12.3292 *lens_ipow(begin_dy, 3) + 0.22938 *begin_dx*lens_ipow(begin_dy, 2) + 12.0101 *lens_ipow(begin_dx, 2)*begin_dy + 1.89749 *begin_y*lens_ipow(begin_dy, 2) + 0.683323 *begin_y*lens_ipow(begin_dx, 2) + 0.0836871 *lens_ipow(begin_y, 2)*begin_dy + -0.000110599 *lens_ipow(begin_y, 2)*begin_dx + -0.000573822 *lens_ipow(begin_y, 3) + 1.24021 *begin_x*begin_dx*begin_dy + 0.0415115 *begin_x*begin_y*begin_dx + 0.0332036 *lens_ipow(begin_x, 2)*begin_dy + -0.000570228 *lens_ipow(begin_x, 2)*begin_y + -0.297595 *begin_y*lens_ipow(begin_lambda, 3) + 0.0132093 *begin_x*begin_y*begin_dx*begin_lambda + -0.00427003 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.0572767 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + -9.94302 *begin_dy*lens_ipow(begin_lambda, 5) + 3.70884 *lens_ipow(begin_dx, 2)*begin_dy*lens_ipow(begin_lambda, 4) + -1.48449 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 4) + 0.412592 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*begin_dy + 1.45067e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx + -1.13532e-05 *lens_ipow(begin_x, 5)*begin_dx*begin_dy + 1.28836e-07 *lens_ipow(begin_x, 5)*begin_y*begin_dx + -2.39727e-05 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.00473359 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 5) + -30.3621 *begin_x*begin_y*lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 2) + 0.0285679 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -1.62746e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 2) + 2.17972e-09 *lens_ipow(begin_y, 8)*begin_dy*begin_lambda + -0.050333 *begin_x*begin_y*begin_dx*lens_ipow(begin_lambda, 7) + 39.8224 *begin_dy*lens_ipow(begin_lambda, 10) + 1.59944 *begin_y*lens_ipow(begin_lambda, 10) + 778.163 *begin_y*lens_ipow(begin_dy, 10) + -1.30548e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 7)*lens_ipow(begin_lambda, 2) + -1.77923e-10 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*lens_ipow(begin_lambda, 2);
    out[2] =  + -1.11918e-05  + -0.225092 *begin_dx + -0.0841526 *begin_x + -0.00133091 *begin_dx*begin_dy + 0.691353 *begin_dx*lens_ipow(begin_dy, 2) + 0.684331 *lens_ipow(begin_dx, 3) + 0.0445784 *begin_y*begin_dx*begin_dy + 0.00135276 *lens_ipow(begin_y, 2)*begin_dx + 0.0180182 *begin_x*lens_ipow(begin_dy, 2) + 0.0627794 *begin_x*lens_ipow(begin_dx, 2) + 0.0014138 *begin_x*begin_y*begin_dy + 6.7031e-05 *begin_x*lens_ipow(begin_y, 2) + 0.00269862 *lens_ipow(begin_x, 2)*begin_dx + 8.04753e-05 *lens_ipow(begin_x, 3) + -0.125919 *begin_dx*lens_ipow(begin_lambda, 4) + 0.00229266 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -9.59623e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -0.000933466 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3) + -6.95202e-06 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + 0.0641112 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -3.04562e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 6.48907e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -819.678 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 6) + -5.14268e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 3)*begin_dy + -0.00176443 *begin_x*lens_ipow(begin_lambda, 8) + -0.0155363 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_dy, 5) + 8.81332e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5) + -0.00502245 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 6) + -5.07927e-12 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6) + -2.74458e-08 *lens_ipow(begin_x, 6)*begin_dx*lens_ipow(begin_lambda, 2) + -1110.68 *lens_ipow(begin_dx, 7)*lens_ipow(begin_dy, 2)*begin_lambda + -396.017 *lens_ipow(begin_dx, 9)*lens_ipow(begin_lambda, 2) + -0.121145 *begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 8) + -1.11794 *begin_x*lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 6) + -3.65549e-15 *begin_x*lens_ipow(begin_y, 10) + 1.27568e-08 *lens_ipow(begin_x, 6)*begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -4.3603e-10 *lens_ipow(begin_x, 7)*lens_ipow(begin_lambda, 4) + -4.19365e-14 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 4) + -1.78293e-14 *lens_ipow(begin_x, 9)*lens_ipow(begin_y, 2) + -3.29003e-15 *lens_ipow(begin_x, 11);
    out[3] =  + 1.42263e-06  + -0.217603 *begin_dy + -0.0841902 *begin_y + 1.58352e-06 *begin_x + 0.674901 *lens_ipow(begin_dy, 3) + 0.0628713 *begin_y*lens_ipow(begin_dy, 2) + 0.000197341 *begin_y*begin_dx*begin_dy + 0.0140972 *begin_y*lens_ipow(begin_dx, 2) + 0.00271882 *lens_ipow(begin_y, 2)*begin_dy + 8.19755e-05 *lens_ipow(begin_y, 3) + 0.037641 *begin_x*begin_dx*begin_dy + 0.00114241 *begin_x*begin_y*begin_dx + 0.00116084 *lens_ipow(begin_x, 2)*begin_dy + 9.25026e-05 *lens_ipow(begin_x, 2)*begin_y + -0.104654 *begin_dy*lens_ipow(begin_lambda, 3) + 0.901056 *lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + 1.97743e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.0122638 *begin_x*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000485762 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -4.04272e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + 0.0670327 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.000863194 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy + 0.030737 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 5) + 0.0318101 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*begin_dy + -6.17453e-10 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -1.54031e-05 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 3) + -0.000968929 *begin_y*lens_ipow(begin_lambda, 7) + 0.000134698 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 5) + -3.46165e-08 *lens_ipow(begin_y, 6)*begin_dy*lens_ipow(begin_lambda, 2) + -8.41654e-13 *lens_ipow(begin_y, 9) + 4.0835e-08 *lens_ipow(begin_x, 6)*lens_ipow(begin_dy, 3) + 2.80108e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4)*begin_dx*begin_dy*begin_lambda + -347.408 *lens_ipow(begin_dy, 9)*lens_ipow(begin_lambda, 2) + -6838.91 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 9) + -1.13772 *begin_y*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 6) + -5.19551e-10 *lens_ipow(begin_y, 7)*lens_ipow(begin_lambda, 4) + 1.86325e-11 *begin_x*lens_ipow(begin_y, 8)*begin_dx*begin_dy + 1.39228e-05 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 2.12759e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -2.86344e-14 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 3);
    pred_out_cs=[0,0,0,0,0,0];
    lens_sphereToCs(out, pred_out_cs, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
    var view =
    [
      scene_x - pred_out_cs[0],
      scene_y - pred_out_cs[1],
      scene_z - pred_out_cs[2]
    ];
    var iviewlen = 1.0/Math.sqrt(view[0]*view[0] + view[1]*view[1] + view[2]*view[2]);
    for(var i=0;i<3;i++) view[i] *= iviewlen;
    out_new = [0,0,0,0,0];
    pred_out_cs[3] = view[0];
    pred_out_cs[4] = view[1];
    pred_out_cs[5] = view[2];
    lens_csToSphere(pred_out_cs, out_new, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
    delta_out = [out_new[2] - out[2], out_new[3] - out[3]];
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    domega2_dx0 = [[0,0],[0,0]];
    domega2_dx0[0][0] =  + -0.0841526  + 0.0180182 *lens_ipow(begin_dy, 2) + 0.0627794 *lens_ipow(begin_dx, 2) + 0.0014138 *begin_y*begin_dy + 6.7031e-05 *lens_ipow(begin_y, 2) + 0.00539724 *begin_x*begin_dx + 0.000241426 *lens_ipow(begin_x, 2) + -1.91925e-05 *begin_x*begin_y*begin_dx*begin_dy + -6.95202e-06 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + 0.128222 *begin_x*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + -6.09124e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_lambda, 2) + 1.94672e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -0.00176443 *lens_ipow(begin_lambda, 8) + -0.0310725 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 5) + 0.000176266 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 5) + -0.0150674 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 6) + -1.52378e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 6) + -1.64675e-07 *lens_ipow(begin_x, 5)*begin_dx*lens_ipow(begin_lambda, 2) + -1.11794 *lens_ipow(begin_dx, 4)*lens_ipow(begin_lambda, 6) + -3.65549e-15 *lens_ipow(begin_y, 10) + 7.65407e-08 *lens_ipow(begin_x, 5)*begin_y*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -3.05221e-09 *lens_ipow(begin_x, 6)*lens_ipow(begin_lambda, 4) + -2.93555e-13 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 4) + -1.60463e-13 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 2) + -3.61904e-14 *lens_ipow(begin_x, 10);
    domega2_dx0[0][1] =  + 0.0445784 *begin_dx*begin_dy + 0.00270553 *begin_y*begin_dx + 0.0014138 *begin_x*begin_dy + 0.000134062 *begin_x*begin_y + 0.00458532 *begin_y*lens_ipow(begin_dx, 3) + -9.59623e-06 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -0.0028004 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + -2.08561e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -6.09124e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_lambda, 2) + 1.29781e-06 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dy, 2) + -2.57134e-05 *lens_ipow(begin_y, 4)*lens_ipow(begin_dx, 3)*begin_dy + -0.0155363 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 5) + 0.000176266 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 5) + -3.04756e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5) + -0.121145 *begin_dx*begin_dy*lens_ipow(begin_lambda, 8) + -3.65549e-14 *begin_x*lens_ipow(begin_y, 9) + 1.27568e-08 *lens_ipow(begin_x, 6)*begin_dx*begin_dy*lens_ipow(begin_lambda, 2) + -1.67746e-13 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 3) + -3.56585e-14 *lens_ipow(begin_x, 9)*begin_y;
    domega2_dx0[1][0] =  + 1.58352e-06  + 0.037641 *begin_dx*begin_dy + 0.00114241 *begin_y*begin_dx + 0.00232168 *begin_x*begin_dy + 0.000185005 *begin_x*begin_y + -0.0122638 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000485762 *begin_y*begin_dx*lens_ipow(begin_dy, 2) + -8.08543e-06 *begin_x*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -0.000863194 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*begin_dy + 0.061474 *begin_x*lens_ipow(begin_dy, 5) + 0.0636202 *begin_x*lens_ipow(begin_dx, 4)*begin_dy + -1.23491e-09 *begin_x*lens_ipow(begin_y, 5) + -4.62094e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3) + 2.4501e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 3) + 8.40323e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dx*begin_dy*begin_lambda + 1.86325e-11 *lens_ipow(begin_y, 8)*begin_dx*begin_dy + 5.56914e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 8.51035e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -2.29075e-13 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 3);
    domega2_dx0[1][1] =  + -0.0841902  + 0.0628713 *lens_ipow(begin_dy, 2) + 0.000197341 *begin_dx*begin_dy + 0.0140972 *lens_ipow(begin_dx, 2) + 0.00543763 *begin_y*begin_dy + 0.000245926 *lens_ipow(begin_y, 2) + 0.00114241 *begin_x*begin_dx + 9.25026e-05 *lens_ipow(begin_x, 2) + 5.93229e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.000485762 *begin_x*begin_dx*lens_ipow(begin_dy, 2) + -8.08543e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy*begin_lambda + 0.134065 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.00172639 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -3.08727e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + -1.54031e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + -0.000968929 *lens_ipow(begin_lambda, 7) + 0.00053879 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 5) + -2.07699e-07 *lens_ipow(begin_y, 5)*begin_dy*lens_ipow(begin_lambda, 2) + -7.57489e-12 *lens_ipow(begin_y, 8) + 1.12043e-07 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 3)*begin_dx*begin_dy*begin_lambda + -1.13772 *lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 6) + -3.63686e-09 *lens_ipow(begin_y, 6)*lens_ipow(begin_lambda, 4) + 1.4906e-10 *begin_x*lens_ipow(begin_y, 7)*begin_dx*begin_dy + 2.78457e-05 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 6.38276e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 2) + -8.59032e-14 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 2);
    invJ = [[0,0],[0,0]];
    invdet = 1.0/(domega2_dx0[0][0]*domega2_dx0[1][1] - domega2_dx0[0][1]*domega2_dx0[1][0]);
    invJ[0][0] =  domega2_dx0[1][1]*invdet;
    invJ[1][1] =  domega2_dx0[0][0]*invdet;
    invJ[0][1] = -domega2_dx0[0][1]*invdet;
    invJ[1][0] = -domega2_dx0[1][0]*invdet;
    for(var i=0;i<2;i++)
    {
      sensor[0] += 0.5*invJ[0][i]*delta_out[i];
      sensor[1] += 0.5*invJ[1][i]*delta_out[i];
    }
    if(sqr_err>prev_sqr_err) error |= 1;
    if(sqr_ap_err>prev_sqr_ap_err) error |= 2;
    if(out[0]!=out[0]) error |= 4;
    if(out[1]!=out[1]) error |= 8;
    // reset error code for first few iterations.
    if(k<10) error = 0;

    // visualise newton error deltas:
    d = 'M' + (-pred_out_cs[2]) + ' ' + pred_out_cs[1] + ' L'+(-scene_z)+' '+scene_y;
    set_ray(d, 1337, 0);
    d = 'M' + (aperturepointer.x) +' '+aperturepointer.y+' L'+(aperturepointer.x)+' '+(aperturepointer.y-delta_ap[1]);
    set_ray(d, 1338, 0);
    // now the update delta ones:
    lens_length=0;
    for(var i=0;i<lenses.length;i++)
      lens_length+=lenses[i][LENS_THICKNESS];
    d = 'M' + lens_length +' '+(sensor[1])+' L'+(lens_length)+' '+(sensor[1] - invJ[1][0]*delta_out[0]-invJ[1][1]*delta_out[1]);
    set_ray(d, 2337, 0);
    d = 'M' + (lens_length) +' '+(sensor[1])+' L'+(lens_length-10)+' '+(sensor[1]+10*sensor[3]);
    set_ray(d, 2338, 0);
    // if(k<100&&(sqr_err>eps||sqr_ap_err>eps)&&error==0)
    // {
    //   setTimeout(lt_aperture_sample_angenieux, 150,
    //       lenses, ap_x, ap_y, scene_x, scene_y, scene_z, sensor, out, k);
    //   return error;
    // }
  }
  if(out[0]*out[0]+out[1]*out[1] > lens_outer_pupil_radius*lens_outer_pupil_radius) error |= 16;
  // converged and all good! mark in green:
  opp = [0,0,0,0,0,0];
  raytrace_from_sensor(lenses, sensor, opp);
  var path = document.getElementById('lens_ray666');
  if(!path) return error;
  if(!error) path.setAttribute('stroke', '#00B484');
  set_ray('',1337,1);
  set_ray('',1338,1);
  set_ray('',2337,1);
  set_ray('',2338,1);

  /*
const float begin_x = x;
const float begin_y = y;
const float begin_dx = dx;
const float begin_dy = dy;
const float begin_lambda = lambda;
if(error==0)
  out[4] =  + 0.342711  + 0.000440003 *begin_dx + -1.3641e-05 *begin_y + -0.0212986 *lens_ipow(begin_dy, 2) + 0.0100276 *lens_ipow(begin_dx, 2) + -0.00147191 *begin_y*begin_dy + -0.000195131 *lens_ipow(begin_y, 2) + -0.000134612 *begin_x*begin_dy + -0.00112554 *begin_x*begin_dx + -1.04342e-05 *begin_x*begin_y + -0.000339083 *lens_ipow(begin_x, 2) + 0.154404 *lens_ipow(begin_lambda, 3) + 0.000531604 *begin_x*lens_ipow(begin_dy, 2) + -6.42984e-07 *begin_x*lens_ipow(begin_y, 2) + -7.35433e-08 *lens_ipow(begin_x, 3) + -0.00716811 *begin_y*lens_ipow(begin_dx, 3) + -0.00065809 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 2.90187e-06 *lens_ipow(begin_y, 3)*begin_dx + -0.000714094 *begin_x*begin_y*begin_dx*begin_dy + -0.000895059 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 3.92795e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 3.79168e-06 *lens_ipow(begin_x, 4) + -6.62643e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.000270438 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + 1.52297e-08 *lens_ipow(begin_y, 6) + 2.14202e-07 *lens_ipow(begin_x, 4)*begin_y*begin_dy + -8.38774e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -1.68292e-10 *lens_ipow(begin_x, 8) + 2.78652e-10 *lens_ipow(begin_y, 8)*lens_ipow(begin_dx, 2) + -8.78601e-13 *lens_ipow(begin_y, 10) + -3.68121e-12 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 8) + -2.36591e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dx*begin_dy + -4.85409e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6) + 5.46354e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 5) + -8.44642e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 4) + 2.06435e-10 *lens_ipow(begin_x, 8)*lens_ipow(begin_dy, 2) + -2.61963e-12 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 2) + -1.11549 *lens_ipow(begin_lambda, 11) + 5.90496e-13 *begin_x*lens_ipow(begin_y, 9)*begin_dx + 1.26894e-14 *lens_ipow(begin_x, 9)*lens_ipow(begin_y, 2);
else
*/
  out[4] = 0.0;
}



function lt_aperture_sample_angenieux_writeout(lenses, ap_x, ap_y, scene_x, scene_y, scene_z, sensor, out, k)
{
  // kill old runs in timeouts:
  if(ap_x != 0.0 || ap_y != aperturepointer.y) return 0;
  if(scene_x != 0.0 || scene_y != mousepointer.y || scene_z != -mousepointer.x) return 0;
  // visualise progress:
  opp = [0,0,0,0,0,0];
  raytrace_from_sensor(lenses, sensor, opp);

  // ap_x = 2.5;
  // ap_y = 2.5;

  scene_x = 0.0;
  scene_y = -2500;
  scene_z = 9999;

  var error = 0;

  var lens_outer_pupil_curvature_radius = lensdb[lens_curr][0][LENS_RADIUS];
  var lens_outer_pupil_radius = lensdb[lens_curr][0][LENS_HOUSING_RADIUS];

  var eps = 1e-8;
  var sqr_err = 1e30, sqr_ap_err = 1e30;
  var prev_sqr_err = 1e32, prev_sqr_ap_err = 1e32;


  var cnt_err_up = 0;
  var cnt_ap_err_up = 0;

  for(;k<100&&(sqr_err>eps||sqr_ap_err>eps)&&error==0;k++)
  {
    console.log("count (k): ", k);
    prev_sqr_err = sqr_err, prev_sqr_ap_err = sqr_ap_err;
    var begin_x = sensor[0];
    var begin_y = sensor[1];
    var begin_dx = sensor[2];
    var begin_dy = sensor[3];
    var begin_lambda = sensor[4];
    console.log("begin_x: ", begin_x);
    console.log("begin_y: ", begin_y);
    console.log("begin_dx: ", begin_dx);
    console.log("begin_dy: ", begin_dy);
    console.log("begin_lambda: ", begin_lambda);
    var pred_ap = [
      + 0.197484 *begin_x + 27.5928 *begin_dx + 1.74497 *begin_dx*begin_lambda + 0.08335 *begin_x*begin_lambda + -0.106556 *begin_y*begin_dx*begin_dy + -0.000436864 *begin_x*lens_ipow(begin_y, 2) + -15.176 *lens_ipow(begin_dx, 3) + -15.544 *begin_dx*lens_ipow(begin_dy, 2) + -0.000420072 *lens_ipow(begin_x, 3) + -0.193987 *begin_x*lens_ipow(begin_dx, 2) + -0.115566 *begin_x*lens_ipow(begin_dy, 2) + 8.53267e-06 *lens_ipow(begin_x, 4)*begin_dx + -1.37132e-09 *lens_ipow(begin_x, 7) + -1.42221e-09 *begin_x*lens_ipow(begin_y, 6) + -4.46795e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4) + -4.32995e-09 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2),
      + 27.5931 *begin_dy + 0.19711 *begin_y + 1.74531 *begin_dy*begin_lambda + 0.0839936 *begin_y*begin_lambda + -0.115586 *begin_y*lens_ipow(begin_dx, 2) + -0.000436985 *lens_ipow(begin_x, 2)*begin_y + -15.2094 *lens_ipow(begin_dy, 3) + -0.000418615 *lens_ipow(begin_y, 3) + -0.194777 *begin_y*lens_ipow(begin_dy, 2) + -15.493 *lens_ipow(begin_dx, 2)*begin_dy + -0.107801 *begin_x*begin_dx*begin_dy + 8.51781e-06 *lens_ipow(begin_y, 4)*begin_dy + -1.40883e-09 *lens_ipow(begin_y, 7) + -4.44726e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 5) + -4.38036e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 3) + -1.37285e-09 *lens_ipow(begin_x, 6)*begin_y
    ];
    console.log("pred_ap: ", pred_ap[0], pred_ap[1]);
    delta_ap = [ap_x - pred_ap[0], ap_y - pred_ap[1]];
    console.log("delta_ap: ", delta_ap[0], delta_ap[1]);
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    console.log("sqr_ap_err: ", sqr_ap_err);
    var dx1_domega0 = [[0,0],[0,0]];
    dx1_domega0[0][0] =  + 27.5928  + 1.74497 *begin_lambda + -0.106556 *begin_y*begin_dy + -45.5281 *lens_ipow(begin_dx, 2) + -15.544 *lens_ipow(begin_dy, 2) + -0.387974 *begin_x*begin_dx + 8.53267e-06 *lens_ipow(begin_x, 4)+0.0;
    dx1_domega0[0][1] =  + -0.106556 *begin_y*begin_dx + -31.0879 *begin_dx*begin_dy + -0.231133 *begin_x*begin_dy+0.0;
    dx1_domega0[1][0] =  + -0.231172 *begin_y*begin_dx + -30.9859 *begin_dx*begin_dy + -0.107801 *begin_x*begin_dy+0.0;
    dx1_domega0[1][1] =  + 27.5931  + 1.74531 *begin_lambda + -45.6282 *lens_ipow(begin_dy, 2) + -0.389554 *begin_y*begin_dy + -15.493 *lens_ipow(begin_dx, 2) + -0.107801 *begin_x*begin_dx + 8.51781e-06 *lens_ipow(begin_y, 4)+0.0;
    console.log("dx1_domaga0: ", dx1_domega0[0][0], dx1_domega0[0][1], dx1_domega0[1][0], dx1_domega0[1][1]);
    invApJ = [[0,0],[0,0]];
    var invdetap = 1.0/(dx1_domega0[0][0]*dx1_domega0[1][1] - dx1_domega0[0][1]*dx1_domega0[1][0]);
    console.log("invdetap: ", invdetap);
    invApJ[0][0] =  dx1_domega0[1][1]*invdetap;
    invApJ[1][1] =  dx1_domega0[0][0]*invdetap;
    invApJ[0][1] = -dx1_domega0[0][1]*invdetap;
    invApJ[1][0] = -dx1_domega0[1][0]*invdetap;
    for(var i=0;i<2;i++)
    {
      sensor[2] += invApJ[0][i]*delta_ap[i];
      sensor[3] += invApJ[1][i]*delta_ap[i];
    }
    console.log("dx: ", sensor[2]);
    console.log("dy: ", sensor[3]);
    out[0] =  + -0.636603 *begin_x + 49.0721 *begin_dx + 0.724233 *begin_x*begin_lambda + -0.00113165 *begin_x*lens_ipow(begin_y, 2) + -20.1743 *lens_ipow(begin_dx, 3) + -20.6523 *begin_dx*lens_ipow(begin_dy, 2) + -0.00139289 *lens_ipow(begin_x, 3) + 0.00630502 *begin_x*begin_y*begin_dy + 0.297063 *begin_x*lens_ipow(begin_dx, 2) + -0.530259 *begin_x*lens_ipow(begin_lambda, 2) + 0.250268 *begin_x*lens_ipow(begin_dy, 2) + 0.00547431 *lens_ipow(begin_y, 2)*begin_dx + 0.000592076 *lens_ipow(begin_x, 3)*begin_lambda + 0.0232881 *lens_ipow(begin_x, 2)*begin_dx*begin_lambda + -3.07406e-09 *lens_ipow(begin_x, 7) + -1.62938e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 4);
    out[1] =  + 49.0535 *begin_dy + -0.467832 *begin_y + 0.104946 *begin_y*begin_lambda + 0.00642504 *begin_x*begin_y*begin_dx + 0.246686 *begin_y*lens_ipow(begin_dx, 2) + -0.000814023 *lens_ipow(begin_x, 2)*begin_y + -20.2681 *lens_ipow(begin_dy, 3) + -0.00138601 *lens_ipow(begin_y, 3) + 0.00567435 *lens_ipow(begin_x, 2)*begin_dy + -20.6771 *lens_ipow(begin_dx, 2)*begin_dy + 0.525409 *begin_y*lens_ipow(begin_dy, 2)*begin_lambda + 0.000714418 *lens_ipow(begin_y, 3)*begin_lambda + 0.0237852 *lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -1.47814e-06 *lens_ipow(begin_x, 4)*begin_y + -3.09117e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + -3.27987e-09 *lens_ipow(begin_y, 7);
    out[2] =  + -0.0123666 *begin_x + -0.609913 *begin_dx + -0.0098959 *begin_x*begin_lambda + 1.35313e-05 *begin_x*lens_ipow(begin_y, 2) + 0.25801 *lens_ipow(begin_dx, 3) + 0.182025 *begin_dx*lens_ipow(begin_dy, 2) + 2.0662e-05 *lens_ipow(begin_x, 3) + 0.00755466 *begin_x*lens_ipow(begin_lambda, 2) + -7.0297e-06 *lens_ipow(begin_x, 3)*begin_lambda + 2.11676e-08 *begin_x*lens_ipow(begin_y, 4) + 4.81488e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + -5.45117e-07 *lens_ipow(begin_x, 3)*begin_y*begin_dy + 0.000931727 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + -9.11762e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 4) + 1.63809e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + -3.04567e-09 *lens_ipow(begin_x, 6)*begin_dx;
    out[3] =  + -0.611143 *begin_dy + -0.0116902 *begin_y + -0.0100684 *begin_y*begin_lambda + -0.000126838 *begin_x*begin_y*begin_dx + -0.00465873 *begin_y*lens_ipow(begin_dx, 2) + 1.00098e-05 *lens_ipow(begin_x, 2)*begin_y + 0.273941 *lens_ipow(begin_dy, 3) + 1.29961e-05 *lens_ipow(begin_y, 3) + 0.357691 *lens_ipow(begin_dx, 2)*begin_dy + 0.00685957 *begin_y*lens_ipow(begin_lambda, 2) + 0.00425551 *begin_x*begin_dx*begin_dy + -5.50655e-07 *lens_ipow(begin_y, 4)*begin_dy + 2.45207e-08 *lens_ipow(begin_x, 4)*begin_y + 4.90176e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3) + 4.62906e-11 *lens_ipow(begin_y, 7) + -3.83828e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dy;
    console.log("out: ", out[0], out[1], out[2], out[3]);
    pred_out_cs=[0,0,0,0,0,0];
    lens_sphereToCs(out, pred_out_cs, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
    console.log("pred_out_cs_pos: ", pred_out_cs[0], pred_out_cs[1], pred_out_cs[2]);
    console.log("pred_out_cs_dir: ", pred_out_cs[3], pred_out_cs[4], pred_out_cs[5]);
    var view =
    [
      scene_x - pred_out_cs[0],
      scene_y - pred_out_cs[1],
      scene_z - pred_out_cs[2]
    ];
    console.log("view: ", view[0], view[1], view[2]);
    var iviewlen = 1.0/Math.sqrt(view[0]*view[0] + view[1]*view[1] + view[2]*view[2]);
    for(var i=0;i<3;i++) view[i] *= iviewlen;
    console.log("view_normalized: ", view[0], view[1], view[2]);
    out_new = [0,0,0,0,0];
    pred_out_cs[3] = view[0];
    pred_out_cs[4] = view[1];
    pred_out_cs[5] = view[2];
    lens_csToSphere(pred_out_cs, out_new, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
    console.log("out_new_pos: ", out_new[0], out_new[1]);
    console.log("out_new_dir: ", out_new[2], out_new[3]);
    delta_out = [out_new[2] - out[2], out_new[3] - out[3]];
    console.log("delta_out: ", delta_out[0], delta_out[1]);
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    console.log("sqr_err: ", sqr_err);
    domega2_dx0 = [[0,0],[0,0]];
    domega2_dx0[0][0] =  + -0.0123666  + -0.0098959 *begin_lambda + 1.35313e-05 *lens_ipow(begin_y, 2) + 6.19861e-05 *lens_ipow(begin_x, 2) + 0.00755466 *lens_ipow(begin_lambda, 2) + -2.10891e-05 *lens_ipow(begin_x, 2)*begin_lambda + 2.11676e-08 *lens_ipow(begin_y, 4) + 9.62976e-05 *begin_x*begin_y*begin_dx*begin_dy + -1.63535e-06 *lens_ipow(begin_x, 2)*begin_y*begin_dy + -0.000273529 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 4) + 8.19045e-10 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -1.8274e-08 *lens_ipow(begin_x, 5)*begin_dx+0.0;
    domega2_dx0[0][1] =  + 2.70627e-05 *begin_x*begin_y + 8.46706e-08 *begin_x*lens_ipow(begin_y, 3) + 4.81488e-05 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -5.45117e-07 *lens_ipow(begin_x, 3)*begin_dy + 0.00186345 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_lambda, 2) + 3.27618e-10 *lens_ipow(begin_x, 5)*begin_y+0.0;
    domega2_dx0[1][0] =  + -0.000126838 *begin_y*begin_dx + 2.00195e-05 *begin_x*begin_y + 0.00425551 *begin_dx*begin_dy + 9.80827e-08 *lens_ipow(begin_x, 3)*begin_y + 9.80352e-08 *begin_x*lens_ipow(begin_y, 3) + -1.53531e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dy+0.0;
    domega2_dx0[1][1] =  + -0.0116902  + -0.0100684 *begin_lambda + -0.000126838 *begin_x*begin_dx + -0.00465873 *lens_ipow(begin_dx, 2) + 1.00098e-05 *lens_ipow(begin_x, 2) + 3.89883e-05 *lens_ipow(begin_y, 2) + 0.00685957 *lens_ipow(begin_lambda, 2) + -2.20262e-06 *lens_ipow(begin_y, 3)*begin_dy + 2.45207e-08 *lens_ipow(begin_x, 4) + 1.47053e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 3.24034e-10 *lens_ipow(begin_y, 6) + -7.67656e-09 *lens_ipow(begin_x, 4)*begin_y*begin_dy+0.0;
    console.log("domega2_dx0: ", domega2_dx0[0][0], domega2_dx0[0][1], domega2_dx0[1][0], domega2_dx0[1][1]);
    invJ = [[0,0],[0,0]];
    invdet = 1.0/(domega2_dx0[0][0]*domega2_dx0[1][1] - domega2_dx0[0][1]*domega2_dx0[1][0]);
    console.log("invdet: ", invdet);
    invJ[0][0] =  domega2_dx0[1][1]*invdet;
    invJ[1][1] =  domega2_dx0[0][0]*invdet;
    invJ[0][1] = -domega2_dx0[0][1]*invdet;
    invJ[1][0] = -domega2_dx0[1][0]*invdet;
    console.log("invJ: ", invJ[0][0], invJ[1][1], invJ[0][1], invJ[1][0]);
    for(var i=0;i<2;i++)
    {
      sensor[0] += 0.5*invJ[0][i]*delta_out[i];
      sensor[1] += 0.5*invJ[1][i]*delta_out[i];
    }
    console.log("x: ", sensor[0]);
    console.log("y: ", sensor[1]);
    if(sqr_err < prev_sqr_err) cnt_err_up = 0;
    if(sqr_ap_err < prev_sqr_ap_err) cnt_ap_err_up = 0;
    if(sqr_err>prev_sqr_err && ++cnt_err_up > 6){
      error |= 1;
      console.log("error |= 1");
    }
    if(sqr_ap_err>prev_sqr_ap_err && ++cnt_ap_err_up > 6){
      error |= 2;
      console.log("error |= 2");
    }
    if(out[0]!=out[0]){
      error |= 4;
      console.log("error |= 4");
    } 
    if(out[1]!=out[1]){
      error |= 8;
      console.log("error |= 8");
    }
    // reset error code for first few iterations.
    if(k<10){
      error = 0;
      console.log("error reset (k<10)");
    }

    
    // visualise newton error deltas:
    d = 'M' + (-pred_out_cs[2]) + ' ' + pred_out_cs[1] + ' L'+(-scene_z)+' '+scene_y;
    set_ray(d, 1337, 0);
    d = 'M' + (aperturepointer.x) +' '+aperturepointer.y+' L'+(aperturepointer.x)+' '+(aperturepointer.y-delta_ap[1]);
    set_ray(d, 1338, 0);
    // now the update delta ones:
    lens_length=0;
    for(var i=0;i<lenses.length;i++)
      lens_length+=lenses[i][LENS_THICKNESS];
    d = 'M' + lens_length +' '+(sensor[1])+' L'+(lens_length)+' '+(sensor[1] - invJ[1][0]*delta_out[0]-invJ[1][1]*delta_out[1]);
    set_ray(d, 2337, 0);
    d = 'M' + (lens_length) +' '+(sensor[1])+' L'+(lens_length-10)+' '+(sensor[1]+10*sensor[3]);
    set_ray(d, 2338, 0);


    // if((k<100&&sqr_err>eps||sqr_ap_err>eps&&error==0))
    // {
    //   setTimeout(lt_aperture_sample_angenieux_writeout, 150,
    //       lenses, ap_x, ap_y, scene_x, scene_y, scene_z, sensor, out, k);
    //   return error;
    // }
  
  }
  if(out[0]*out[0]+out[1]*out[1] > lens_outer_pupil_radius*lens_outer_pupil_radius){
    error |= 16;
    console.log("outer pupil occlusion: ", error);
  }

  var lens_back_focal_length = 27.465837;
  var lens_inner_pupil_radius = 17.245601;
  var px = sensor[0] + sensor[2] * lens_back_focal_length;
  var py = sensor[1] + sensor[3] * lens_back_focal_length; //(note that lens_focal_length is the back focal length, i.e. the distance unshifted sensor -> pupil)
  if (px*px + py*py > Math.abs(lens_inner_pupil_radius*lens_inner_pupil_radius)) {
    error |= 16;
    console.log("inner pupil occlusion");
  }
  // converged and all good! mark in green:
  opp = [0,0,0,0,0,0];
  raytrace_from_sensor(lenses, sensor, opp);
  var path = document.getElementById('lens_ray666');
  if(!path) return error;
  if(!error) path.setAttribute('stroke', '#00B484');
  set_ray('',1337,1);
  set_ray('',1338,1);
  set_ray('',2337,1);
  set_ray('',2338,1);
  /*
const float begin_x = x;
const float begin_y = y;
const float begin_dx = dx;
const float begin_dy = dy;
const float begin_lambda = lambda;
if(error==0)
  out[4] =  + 0.342711  + 0.000440003 *begin_dx + -1.3641e-05 *begin_y + -0.0212986 *lens_ipow(begin_dy, 2) + 0.0100276 *lens_ipow(begin_dx, 2) + -0.00147191 *begin_y*begin_dy + -0.000195131 *lens_ipow(begin_y, 2) + -0.000134612 *begin_x*begin_dy + -0.00112554 *begin_x*begin_dx + -1.04342e-05 *begin_x*begin_y + -0.000339083 *lens_ipow(begin_x, 2) + 0.154404 *lens_ipow(begin_lambda, 3) + 0.000531604 *begin_x*lens_ipow(begin_dy, 2) + -6.42984e-07 *begin_x*lens_ipow(begin_y, 2) + -7.35433e-08 *lens_ipow(begin_x, 3) + -0.00716811 *begin_y*lens_ipow(begin_dx, 3) + -0.00065809 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 2.90187e-06 *lens_ipow(begin_y, 3)*begin_dx + -0.000714094 *begin_x*begin_y*begin_dx*begin_dy + -0.000895059 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2) + 3.92795e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2) + 3.79168e-06 *lens_ipow(begin_x, 4) + -6.62643e-07 *begin_x*lens_ipow(begin_y, 3)*begin_dx + 0.000270438 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + 1.52297e-08 *lens_ipow(begin_y, 6) + 2.14202e-07 *lens_ipow(begin_x, 4)*begin_y*begin_dy + -8.38774e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx*begin_dy + -1.68292e-10 *lens_ipow(begin_x, 8) + 2.78652e-10 *lens_ipow(begin_y, 8)*lens_ipow(begin_dx, 2) + -8.78601e-13 *lens_ipow(begin_y, 10) + -3.68121e-12 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 8) + -2.36591e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5)*begin_dx*begin_dy + -4.85409e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 6) + 5.46354e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 5) + -8.44642e-12 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 4) + 2.06435e-10 *lens_ipow(begin_x, 8)*lens_ipow(begin_dy, 2) + -2.61963e-12 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 2) + -1.11549 *lens_ipow(begin_lambda, 11) + 5.90496e-13 *begin_x*lens_ipow(begin_y, 9)*begin_dx + 1.26894e-14 *lens_ipow(begin_x, 9)*lens_ipow(begin_y, 2);
else
*/
  out[4] = 0.0;
}




function lt_aperture_sample_angenieux(lenses, ap_x, ap_y, scene_x, scene_y, scene_z, sensor, out, k)
{
  // kill old runs in timeouts:
  if(ap_x != 0.0 || ap_y != aperturepointer.y) return 0;
  if(scene_x != 0.0 || scene_y != mousepointer.y || scene_z != -mousepointer.x) return 0;
  // visualise progress:
  opp = [0,0,0,0,0,0];
  raytrace_from_sensor(lenses, sensor, opp);
  var lens_outer_pupil_curvature_radius = lensdb[lens_curr][0][LENS_RADIUS];
  var lens_outer_pupil_radius = lensdb[lens_curr][0][LENS_HOUSING_RADIUS];
  var error = 0;

  var eps = 1e-8;
  var sqr_err = 1e30, sqr_ap_err = 1e30;
  var prev_sqr_err = 1e32, prev_sqr_ap_err = 1e32;
  for(;k<100&&(sqr_err>eps||sqr_ap_err>eps)&&error==0;k++)
  {
    console.log('iteration: ', k);
    prev_sqr_err = sqr_err, prev_sqr_ap_err = sqr_ap_err;
    var begin_x = sensor[0];
    var begin_y = sensor[1];
    var begin_dx = sensor[2];
    var begin_dy = sensor[3];
    var begin_lambda = sensor[4];
    var pred_ap = [
      + 51.0741 *begin_dx + 0.164957 *begin_x + 3.80311 *begin_dx*begin_lambda + -4.3292e-05 *lens_ipow(begin_y, 2) + 0.0746279 *begin_x*begin_lambda + -0.00255573 *begin_x*begin_dy,
      + 51.0449 *begin_dy + 0.172198 *begin_y + 3.92141 *begin_dy*begin_lambda + 0.0903945 *lens_ipow(begin_dy, 2) + 0.061443 *begin_y*begin_lambda + 0.00456087 *begin_y*begin_dy
   ];
    delta_ap = [ap_x - pred_ap[0], ap_y - pred_ap[1]];
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    var dx1_domega0 = [[0,0],[0,0]];
    dx1_domega0[0][0] =    + 51.0741  + 3.80311 *begin_lambda+0.0;
    dx1_domega0[0][1] =  + -0.00255573 *begin_x+0.0;
    dx1_domega0[1][0] =  0.0;
    dx1_domega0[1][1] =  + 51.0449  + 3.92141 *begin_lambda + 0.180789 *begin_dy + 0.00456087 *begin_y+0.0;
    invApJ = [[0,0],[0,0]];
    var invdetap = 1.0/(dx1_domega0[0][0]*dx1_domega0[1][1] - dx1_domega0[0][1]*dx1_domega0[1][0]);
    invApJ[0][0] =  dx1_domega0[1][1]*invdetap;
    invApJ[1][1] =  dx1_domega0[0][0]*invdetap;
    invApJ[0][1] = -dx1_domega0[0][1]*invdetap;
    invApJ[1][0] = -dx1_domega0[1][0]*invdetap;
    for(var i=0;i<2;i++)
    {
      sensor[2] += invApJ[0][i]*delta_ap[i];
      sensor[3] += invApJ[1][i]*delta_ap[i];
    }
    out[0] =  + 92.3584 *begin_dx + 0.0104136 *begin_y + -0.527274 *begin_x + 2.00056 *begin_dx*begin_lambda + -0.0168445 *begin_y*begin_lambda + 0.158455 *begin_x*begin_lambda;
    out[1] =  + 92.1357 *begin_dy + -0.515513 *begin_y + 2.51865 *begin_dy*begin_lambda + 0.138919 *lens_ipow(begin_dy, 2) + 0.137027 *begin_y*begin_lambda + 0.0074765 *begin_y*begin_dy;
    out[2] =  + -0.57236 *begin_dx + -7.10609e-06 *begin_y + -0.00663669 *begin_x + 0.00840292 *begin_dx*begin_lambda + 7.02599e-07 *lens_ipow(begin_y, 2) + -0.000887943 *begin_x*begin_lambda;
    out[3] = + -0.564999 *begin_dy + -0.00678183 *begin_y + 0.00504171 *begin_dy*begin_lambda + -0.000737731 *begin_y*begin_lambda + -2.57503e-05 *begin_y*begin_dy + 8.41898e-07 *begin_x*begin_y;
    pred_out_cs=[0,0,0,0,0,0];
    lens_sphereToCs(out, pred_out_cs, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
    var view =
    [
      scene_x - pred_out_cs[0],
      scene_y - pred_out_cs[1],
      scene_z - pred_out_cs[2]
    ];
    var iviewlen = 1.0/Math.sqrt(view[0]*view[0] + view[1]*view[1] + view[2]*view[2]);
    for(var i=0;i<3;i++) view[i] *= iviewlen;
    out_new = [0,0,0,0,0];
    pred_out_cs[3] = view[0];
    pred_out_cs[4] = view[1];
    pred_out_cs[5] = view[2];
    lens_csToSphere(pred_out_cs, out_new, - lens_outer_pupil_curvature_radius, lens_outer_pupil_curvature_radius);
    delta_out = [out_new[2] - out[2], out_new[3] - out[3]];
    sqr_err = delta_out[0]*delta_out[0]+delta_out[1]*delta_out[1];
    domega2_dx0 = [[0,0],[0,0]];
    domega2_dx0[0][0] =  + -0.00663669  + -0.000887943 *begin_lambda+0.0;
    domega2_dx0[0][1] =  + -7.10609e-06  + 1.4052e-06 *begin_y+0.0;
    domega2_dx0[1][0] =  + 8.41898e-07 *begin_y+0.0;
    domega2_dx0[1][1] =   + -0.00678183  + -0.000737731 *begin_lambda + -2.57503e-05 *begin_dy + 8.41898e-07 *begin_x+0.0;
    invJ = [[0,0],[0,0]];
    invdet = 1.0/(domega2_dx0[0][0]*domega2_dx0[1][1] - domega2_dx0[0][1]*domega2_dx0[1][0]);
    invJ[0][0] =  domega2_dx0[1][1]*invdet;
    invJ[1][1] =  domega2_dx0[0][0]*invdet;
    invJ[0][1] = -domega2_dx0[0][1]*invdet;
    invJ[1][0] = -domega2_dx0[1][0]*invdet;
    for(var i=0;i<2;i++)
    {
      sensor[0] += invJ[0][i]*delta_out[i];
      sensor[1] += invJ[1][i]*delta_out[i];
    }
    if(sqr_err>prev_sqr_err) error |= 1;
    if(sqr_ap_err>prev_sqr_ap_err) error |= 2;
    if(out[0]!=out[0]) error |= 4;
    if(out[1]!=out[1]) error |= 8;
    // reset error code for first few iterations.
    if(k<10) error = 0;

    // visualise newton error deltas:
    // d = 'M' + (-pred_out_cs[2]) + ' ' + pred_out_cs[1] + ' L'+(-scene_z)+' '+scene_y;
    // set_ray(d, 1337, 0);
    // d = 'M' + (aperturepointer.x) +' '+aperturepointer.y+' L'+(aperturepointer.x)+' '+(aperturepointer.y-delta_ap[1]);
    // set_ray(d, 1338, 0);
    // now the update delta ones:
    // lens_length=0;
    // for(var i=0;i<lenses.length;i++)
    //   lens_length+=lenses[i][LENS_THICKNESS];
    // d = 'M' + lens_length +' '+(sensor[1])+' L'+(lens_length)+' '+(sensor[1] - invJ[1][0]*delta_out[0]-invJ[1][1]*delta_out[1]);
    // set_ray(d, 2337, 0);
    // d = 'M' + (lens_length) +' '+(sensor[1])+' L'+(lens_length-10)+' '+(sensor[1]+10*sensor[3]);
    // set_ray(d, 2338, 0);

    if(k<100&&(sqr_err>eps||sqr_ap_err>eps)&&error==0)
    {
      setTimeout(lt_aperture_sample_angenieux, 60,
          lenses, ap_x, ap_y, scene_x, scene_y, scene_z, sensor, out, k);
      return error;
    }
  }
  if(out[0]*out[0]+out[1]*out[1] > lens_outer_pupil_radius*lens_outer_pupil_radius) error |= 16;
  // converged and all good! mark in green:
  opp = [0,0,0,0,0,0];
  raytrace_from_sensor(lenses, sensor, opp);
  var path = document.getElementById('lens_ray666');
  if(!path) return error;
  if(error==0){
    path.setAttribute('stroke', '#00B484'); // green
  } else {
    path.setAttribute('stroke', '#FF0000'); //red
  }
  console.log('error code: ', error);
  console.log('sensor [', sensor[0], ', ', sensor[1], ', ', sensor[2], ', ', sensor[4], ']');
  // set_ray('',1337,1);
  // set_ray('',1338,1);
  // set_ray('',2337,1);
  // set_ray('',2338,1);

  /*
const float begin_x = x;
const float begin_y = y;
const float begin_dx = dx;
const float begin_dy = dy;
const float begin_lambda = lambda;
if(error==0)
  out[4] =  + 0.330905  + 0.347233 *begin_lambda + -0.236711 *lens_ipow(begin_lambda, 2) + -0.0574053 *lens_ipow(begin_dy, 2) + -0.0610943 *lens_ipow(begin_dx, 2) + -0.000262871 *begin_x*begin_dx;
else
*/
  out[4] = 0.0;
}


lens_init(0);
ROOT_NODE.addEventListener("mousedown", handle_lens_event);
