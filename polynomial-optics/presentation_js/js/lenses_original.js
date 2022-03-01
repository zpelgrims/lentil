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
var ray_scale = 1.0;
var ray_par = 0;
var ray_freeze = 0;

// lens_radius, thickness, ior, vno, housing_radius
var LENS_RADIUS=0;
var LENS_THICKNESS=1;
var LENS_IOR=2;
var LENS_VNO=3;
var LENS_HOUSING_RADIUS=4;

var lens_curr = 0;
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
lensdb_name[lensdb_cnt] = 'fisheye-aspheric';
lensdb[lensdb_cnt++] = [
[40.82   , 2.0    ,1.883 ,40.81 ,22     ],
[12.969  ,12.306  ,1.    ,1.    ,12.7   ],
[-36.811 , 1.5    ,1.883 ,40.81 ,12.7   ],
[22.349  , 4.408  ,1.    ,1.    ,12.7   ],
[90.887  , 4.119  ,2.001 ,25.46 ,12.7   ],
[-37.463 ,10.671  ,1.    ,1.    ,12.7   ],
[19.865  , 4.906  ,1.497 ,81.56 , 9     ],
[-19.386 , 5.0    ,1.    ,1.    , 9     ],
[100000  , 1.1    ,1.    ,0.    , 6     ], // iris
[67.768  , 1.0    ,1.821 ,24.06 , 6     ],
[17.746  , 3.083  ,1.    ,1.    , 6     ],
[22.334  , 1.0    ,2.001 ,25.46 ,10     ],
[17.027  , 2.141  ,1.497 ,81.61 ,10     ],
[31.952  , 0.671  ,1.    ,1.    ,10     ],
[43.402  , 4.088  ,1.497 ,81.61 ,10     ],
[-21.82  , 1.0    ,2.003 ,19.32 ,10     ],
[-29.68  , 0.3    ,1.    ,1.    ,10     ],
[31.251  , 2.707  ,1.883 ,40.81 ,12.0   ],
[76.213  , 1.0    ,1.    ,1.    ,12.0   ],
[100000  , 3.0    ,1.517 ,64.20 ,12.9   ],
[100000  ,14.0    ,1.    ,1.    ,12.9   ],
];
lensdb_name[lensdb_cnt] = 'angenieux';
lensdb[lensdb_cnt++] = [
// // simple lens, abbe 0 indicates iris
// [35.0, 20.0, 1.5, 54.0, 15.0],    // begin bk7 lens
// [-35.0, 1.73, 1.0, 100.0, 15.0],  // end lens
// [100000.0, 30.0, 1.0, 0.0, 15.0], // iris
// angenieux:
[164.12,		10.99	,			1.673	, 32.2	,54],
[559.28,		0.23	,			1.0   , 1.0	  ,54],
[100.12,		11.45	,			1.67	, 47.1  ,51],
[213.54,		0.23	,		  1.0   , 1.0		,51],
[58.04 , 	22.95		, 		1.691	, 54.7	,41],
[2551	 , 2.58			,   	1.673	, 32.2	,41],
[32.39 , 	15.66		,	    1.0   , 1.0		,27],
[10000 , 	15.00		,	    1.0   , 0.0		,25.5], // iris
[-40.42,		2.74	,			1.699	, 30.1	,25],
[192.98,		27.92	,			1.62	, 60.3	,36],
[-55.53,		0.23	,		  1.0   , 1.0		,36],
[192.98,		7.98	,			1.691	, 54.7	,35],
[-225.28,		0.23	,	 	  1.0   , 1.0		,35],
[175.1,		8.48		,		  1.691 ,	54.7	,35],
[-203.54,		55.742,	    1.0   , 1.0	,35],
];
lensdb_name[lensdb_cnt] = 'wideangle'; // 1971 one
lensdb[lensdb_cnt++] = [
[96.15, 7.00, 1.64, 58.1, 50.0], 
[53.85, 17.38, 1.0, 1.0, 50.0], 
[117.48, 5.59, 1.58904, 53.2, 45.0], 
[69.93, 52.45, 1.0, 1.0, 45.0], 
[106.64, 15.73, 1.76684, 46.2, 25.0], 
[-188.11, 4.90, 1.0, 1.0, 25.0], 
[-192.31, 15.38, 1.76684, 27.5, 25.0], 
[-140.91, 9.58, 1.0, 1.0, 25.0], 
[100000, 10.0, 1.0, 0.0, 25.0], //iris
[-65.04, 16.22, 1.7552, 27.5, 25.0], 
[188.11, 2.52, 1.0, 1.0, 25.0], 
[-323.43, 7.00, 1.713, 53.9, 25.0], 
[-65.39, 0.18, 1.0, 1.0, 25.0], 
[-8741.25, 6.64, 1.6583, 57.3, 30.0], 
[-117.55, 131.19, 1.0, 1.0, 30.0], 
];
lensdb_name[lensdb_cnt] = 'fisheye';
lensdb[lensdb_cnt++] = [
[113.47, 7.0, 1.51729, 64.3, 107.5],
[52.63, 28.0, 1.0, 1.0, 52.25],
[76.4, 3.8, 1.51707, 64.1, 50.6],
[33.0, 21.2, 1.0, 1.0, 31.5],
[125.114, 3.0, 1.51707, 64.1, 28.6],
[17.1, 16.5, 1.0, 1.0, 16.5],
[-40.0, 5.0, 1.69037, 54.9, 16.5],
[20.0, 15.0, 1.68871, 31.1, 16.5],
[139.1, 12.0, 1.0, 1.0, 16.5],
[10000, 12.0, 1.0, 0.0, 16.5], // iris
[600, 3.0, 1.61995, 60.4, 16.5],
[-234.7, 0.1, 1.0, 1.0, 16.5],
[53.0, 7.0, 1.48617, 82.0, 16.5],
[-53.0, 1.2, 1.60321, 38.1, 16.5],
[55.0, 4.7, 1.61624, 31.0, 16.5],
[-788.91, 48.1, 1.0, 1.0,   16.5],
[48.78, 4.7, 1.48617, 82.0, 15.0],
[-44.5, 0.7, 1.60294, 38.1, 15.0],
[63.1, 4.0, 1.61624, 31.0,  15.0],
[1077.78, 1.0, 1.0, 1.0,    15.0],
// [40.0, 4.7, 1.48617, 82.0,  15.0],
[40.0, 4.7, 1.7617, 82.0,  14.5],
[-60.0, 0.8, 1.68871, 31.1, 14.5],
[-1466.043, 65.0, 1.61995, 60.4, 14.5],
];
lensdb_name[lensdb_cnt] = 'canon zoom';
lensdb[lensdb_cnt++] = [
[311.919, 2.80, 1.7495, 35, 38     ],
[118.63, 0.42, 1.0, 1.0, 38        ],
[128.135, 8.68, 1.497, 81.6, 38    ],
[-263.46, 0.1, 1.0, 1.0, 38        ],
[79.501, 5.72, 1.4978, 1.6, 35     ],
[203.191, 8.78, 1.0, 1.0, 35       ],
[54.391, 2.2, 1.847, 23.8, 28      ],
[45.859, 1.13, 1.0, 1.0, 28        ],
[51.927, 8.55, 1.487, 70.2, 28     ],
[5099.30, 1.64, 1.0, 1.0, 28       ],
[-488.6, 1.4, 1.804, 46.6, 18      ],
[35.390, 5.88, 1.0, 1.0, 18        ],
[-78.125, 1.4, 1.487, 70.2, 18     ],
[38.137, 4.97, 1.847, 23.9, 18     ],
[417.478, 2.65, 1.0, 1.0, 18       ],
[-66.802, 1.4, 1.729, 54.7, 18,    ],
[-3363.0, 30.32, 1.0, 1.0, 18      ],
[247.12, 3.49, 1.697, 55.5, 19     ],
[-99.902, 0.15, 1.0, 1.0, 19       ],
[-189.99, 4.77, 1.497, 81.6, 19    ],
[-40.553, 1.45, 1.834, 37.2, 19    ],
[-76.277, 14.7, 1.0, 1.0, 19       ],
[58.421, 3.53, 1.804, 46.6, 21     ],
[133.262, 3, 1.0, 1.0, 21          ],
[10000, 0.24, 1.0, 0.0, 21         ],
[34.132, 6.35, 1.497, 81.6, 21     ],
[2256.763, 3.72, 1.620, 36.3, 21   ],
[31.519, 28.17, 1.0, 1.0, 21       ],
[132.947, 5.9, 1.517, 52.4, 21,    ],
[-77.546, 13.94, 1.0, 1.0, 21      ],
[-39.485, 1.8, 1.834, 37.2, 21     ],
[-95.683, 0.15, 1.0, 1.0, 21       ],
[147.644, 3.62, 1.743, 49.3, 21    ],
[-205.76, 54.5, 1.0, 1.0, 21       ],
];
lensdb_name[lensdb_cnt] = 'tessar';
lensdb[lensdb_cnt++] = [
[42.970 ,  9.8   , 1.691, 54.7, 19.2],
[-115.33,  2.1   , 1.549, 45.4, 19.2],
[306.840,  4.16  , 1.0  , 1.0 , 19.2],
[10000  ,  4.0   , 1.0  , 0.0 , 15.0],
[-59.060,  1.870 , 1.640, 34.6, 17.3],
[ 40.930,  10.640, 1.0  , 1.0 , 17.3],
[183.920,  7.050 , 1.691, 54.7, 16.5],
[-48.910,  79.831, 1.0  , 1.0 , 16.5],
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
      sensor = [0,0,0,0,0.5];
      error = lt_aperture_sample_fisheye_ii(lensdb[lens_curr], 0.0, m.y, 0.0, mousepointer.y, -mousepointer.x, sensor, out, 0);
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
  rect.setAttribute('stroke-width', .8/global_scale);
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
      path.setAttribute('stroke-width', 3./global_scale);
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
  d += ' L' + (lens_length - pos[2] - dir[2]*120)+' ' + (pos[dim_up] + dir[dim_up]*120);
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

  var eps = 1e-4;
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
    //   setTimeout(lt_aperture_sample_fisheye_ii, 30,
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

function lt_aperture_sample_fisheye_aspheric(lenses, ap_x, ap_y, scene_x, scene_y, scene_z, sensor, out)
{
//input: scene_[x,y,z] - point in scene, ap_[x,y] - point on aperture, sensor_lambda
//output: sensor_[x,y,dx,dy] point and direction on sensor
  var lens_outer_pupil_curvature_radius = lensdb[lens_curr][0][LENS_RADIUS];
  var lens_outer_pupil_radius = lensdb[lens_curr][0][LENS_HOUSING_RADIUS];
  var error = 0;

  var eps = 1e-8;
  var sqr_err = 1e30, sqr_ap_err = 1e30;
  var prev_sqr_err = 1e32, prev_sqr_ap_err = 1e32;
  for(var k=0;k<100&&(sqr_err>eps||sqr_ap_err>eps)&&error==0;k++)
  {
    prev_sqr_err = sqr_err, prev_sqr_ap_err = sqr_ap_err;
    var begin_x = sensor[0];
    var begin_y = sensor[1];
    var begin_dx = sensor[2];
    var begin_dy = sensor[3];
    var begin_lambda = sensor[4];
    pred_ap = [
       + -0.000159434  + 0.000770307 *begin_dy + 24.6055 *begin_dx + 0.734153 *begin_x + 0.016583 *begin_dx*begin_dy + -1.68856e-05 *begin_x*begin_y + 7.05228e-06 *lens_ipow(begin_x, 2) + -4.55797 *begin_dx*lens_ipow(begin_dy, 2) + 0.441385 *lens_ipow(begin_dx, 3) + 0.228808 *begin_y*begin_dx*begin_dy + -0.000257308 *begin_x*lens_ipow(begin_dy, 2) + 0.824312 *begin_x*lens_ipow(begin_dx, 2) + 0.00959058 *begin_x*begin_y*begin_dy + -0.000479473 *begin_x*lens_ipow(begin_y, 2) + 0.0262756 *lens_ipow(begin_x, 2)*begin_dx + -0.00043652 *lens_ipow(begin_x, 3) + 0.223301 *begin_dx*lens_ipow(begin_lambda, 4) + 0.0571661 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 1.76615e-05 *lens_ipow(begin_y, 4)*begin_dx + -0.166596 *begin_x*begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.0605065 *lens_ipow(begin_x, 2)*begin_dx*lens_ipow(begin_dy, 2) + -0.00307167 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.00263385 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 0.00725299 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3) + 2.83528 *begin_x*lens_ipow(begin_dy, 6) + -8.22726e-09 *begin_x*lens_ipow(begin_y, 6) + 0.00581975 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.000562152 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + -3.14547e-08 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2) + 965.191 *lens_ipow(begin_dx, 7)*lens_ipow(begin_dy, 2) + -97.9529 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 5) + 0.655337 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 7) + -0.00375472 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 1.62838e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 4) + 2.29825e-05 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 4) + 2258.71 *begin_dx*lens_ipow(begin_dy, 10) + 546.724 *lens_ipow(begin_dx, 11) + -1.60584e-12 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 6) + 3.35294e-12 *lens_ipow(begin_x, 9)*begin_y*begin_dy + -1.34645e-13 *lens_ipow(begin_x, 11),
       + -0.000504057  + 24.4896 *begin_dy + 0.734653 *begin_y + -1.4647e-05 *begin_x + -0.000447903 *begin_y*begin_dy + 2.69234 *lens_ipow(begin_dy, 3) + -1.3304 *lens_ipow(begin_dx, 2)*begin_dy + 0.977715 *begin_y*lens_ipow(begin_dy, 2) + 0.0293334 *lens_ipow(begin_y, 2)*begin_dy + -0.000455435 *lens_ipow(begin_y, 3) + 0.602254 *begin_x*begin_dx*begin_dy + 0.0149012 *begin_x*begin_y*begin_dx + 0.00749679 *lens_ipow(begin_x, 2)*begin_dy + -0.000423375 *lens_ipow(begin_x, 2)*begin_y + 38.9603 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + -0.00380116 *begin_y*lens_ipow(begin_lambda, 4) + 0.972792 *begin_y*lens_ipow(begin_dx, 4) + 0.00201857 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.203851 *begin_x*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -0.00560832 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.0427062 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 3) + 1.70134e-05 *lens_ipow(begin_x, 4)*begin_dy + 110.564 *lens_ipow(begin_dx, 6)*begin_dy + 0.00310089 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3)*begin_dy + 2.06896e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 4) + -1.93077e-09 *lens_ipow(begin_y, 7)*lens_ipow(begin_dx, 2) + 1.1694e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 4) + -2.80142e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 3) + -1.98816e-10 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3) + -21.8194 *begin_y*lens_ipow(begin_dx, 4)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 2.06464e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*begin_dx*begin_dy*begin_lambda + 598.714 *lens_ipow(begin_dy, 11) + -1.20619e-13 *lens_ipow(begin_y, 11) + -98.6784 *begin_x*begin_dx*lens_ipow(begin_dy, 9) + -1.50362e-09 *begin_x*lens_ipow(begin_y, 7)*begin_dx*lens_ipow(begin_lambda, 2) + -6.46326e-13 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 9) + -1.50441e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 7) + -1.56042e-08 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 3) + -1.23945e-12 *lens_ipow(begin_x, 10)*begin_dy + -1.2668e-13 *lens_ipow(begin_x, 10)*begin_y
    ];
    delta_ap = [ap_x - pred_ap[0], ap_y - pred_ap[1]];
    sqr_ap_err = delta_ap[0]*delta_ap[0]+delta_ap[1]*delta_ap[1];
    var dx1_domega0 = [[0,0],[0,0]];
    dx1_domega0[0][0] =  + 24.6055  + 0.016583 *begin_dy + -4.55797 *lens_ipow(begin_dy, 2) + 1.32415 *lens_ipow(begin_dx, 2) + 0.228808 *begin_y*begin_dy + 1.64862 *begin_x*begin_dx + 0.0262756 *lens_ipow(begin_x, 2) + 0.223301 *lens_ipow(begin_lambda, 4) + 0.171498 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 1.76615e-05 *lens_ipow(begin_y, 4) + -0.333192 *begin_x*begin_y*begin_dx*begin_dy + 0.0605065 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -0.00307167 *lens_ipow(begin_x, 2)*begin_y*begin_dy + 0.00725299 *lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 3) + 0.0174592 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 2)*begin_dy + -0.00168645 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + 6756.34 *lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 2) + -293.859 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 5) + 4.58736 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 6) + -0.00750944 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3) + 9.193e-05 *lens_ipow(begin_x, 5)*lens_ipow(begin_dx, 3) + 2258.71 *lens_ipow(begin_dy, 10) + 6013.96 *lens_ipow(begin_dx, 10);
    dx1_domega0[0][1] =  + 0.000770307  + 0.016583 *begin_dx + -9.11595 *begin_dx*begin_dy + 0.228808 *begin_y*begin_dx + -0.000514615 *begin_x*begin_dy + 0.00959058 *begin_x*begin_y + -0.166596 *begin_x*begin_y*lens_ipow(begin_dx, 2) + 0.121013 *lens_ipow(begin_x, 2)*begin_dx*begin_dy + -0.00307167 *lens_ipow(begin_x, 2)*begin_y*begin_dx + 0.0052677 *lens_ipow(begin_x, 3)*begin_dy + 0.021759 *lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 2) + 17.0117 *begin_x*lens_ipow(begin_dy, 5) + 0.00581975 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3) + 1930.38 *lens_ipow(begin_dx, 7)*begin_dy + -489.764 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 4) + -0.0112642 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 22587.1 *begin_dx*lens_ipow(begin_dy, 9) + 3.35294e-12 *lens_ipow(begin_x, 9)*begin_y;
    dx1_domega0[1][0] =  + -2.6608 *begin_dx*begin_dy + 0.602254 *begin_x*begin_dy + 0.0149012 *begin_x*begin_y + 77.9207 *begin_dx*lens_ipow(begin_dy, 3) + 3.89117 *begin_y*lens_ipow(begin_dx, 3) + 0.00403713 *lens_ipow(begin_y, 3)*begin_dx + -0.203851 *begin_x*begin_y*lens_ipow(begin_dy, 2) + -0.00560832 *begin_x*lens_ipow(begin_y, 2)*begin_dy + 663.383 *lens_ipow(begin_dx, 5)*begin_dy + 0.00930268 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 2)*begin_dy + -3.86154e-09 *lens_ipow(begin_y, 7)*begin_dx + 4.67759e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3) + -87.2775 *begin_y*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 3) + 2.06464e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*begin_dy*begin_lambda + -98.6784 *begin_x*lens_ipow(begin_dy, 9) + -1.50362e-09 *begin_x*lens_ipow(begin_y, 7)*lens_ipow(begin_lambda, 2);
    dx1_domega0[1][1] =  + 24.4896  + -0.000447903 *begin_y + 8.07701 *lens_ipow(begin_dy, 2) + -1.3304 *lens_ipow(begin_dx, 2) + 1.95543 *begin_y*begin_dy + 0.0293334 *lens_ipow(begin_y, 2) + 0.602254 *begin_x*begin_dx + 0.00749679 *lens_ipow(begin_x, 2) + 116.881 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.407703 *begin_x*begin_y*begin_dx*begin_dy + -0.00560832 *begin_x*lens_ipow(begin_y, 2)*begin_dx + 0.128119 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 1.70134e-05 *lens_ipow(begin_x, 4) + 110.564 *lens_ipow(begin_dx, 6) + 0.00310089 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 3) + 8.27583e-05 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 3) + -8.40426e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -43.6387 *begin_y*lens_ipow(begin_dx, 4)*begin_dy*lens_ipow(begin_lambda, 3) + 2.06464e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 2)*begin_dx*begin_lambda + 6585.85 *lens_ipow(begin_dy, 10) + -888.106 *begin_x*begin_dx*lens_ipow(begin_dy, 8) + -4.68127e-08 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 2) + -1.23945e-12 *lens_ipow(begin_x, 10);
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
    out[0] =  + 0.000177164  + 9.64591 *begin_dx + -7.08648e-05 *begin_y + -1.08328 *begin_x + -0.00145509 *begin_y*begin_dx + -0.00145057 *begin_x*begin_dy + -7.81265e-05 *begin_x*begin_y + 2.68667 *begin_dx*lens_ipow(begin_dy, 2) + 0.977651 *begin_y*begin_dx*begin_dy + 0.0326945 *lens_ipow(begin_y, 2)*begin_dx + 1.53952 *begin_x*lens_ipow(begin_dx, 2) + 0.0193798 *begin_x*begin_y*begin_dy + 9.63402e-05 *begin_x*lens_ipow(begin_y, 2) + 0.0732042 *lens_ipow(begin_x, 2)*begin_dx + 0.000332878 *lens_ipow(begin_x, 3) + 0.909852 *begin_dx*lens_ipow(begin_lambda, 3) + -0.215166 *begin_x*lens_ipow(begin_lambda, 3) + 39.746 *lens_ipow(begin_dx, 5) + 0.00385704 *lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 2) + 0.145857 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 3) + 0.00730544 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -0.00752869 *lens_ipow(begin_x, 2)*begin_y*begin_dx*begin_dy + 0.00386825 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 2.22 *begin_x*lens_ipow(begin_dy, 4)*begin_lambda + -0.162367 *begin_x*begin_y*lens_ipow(begin_dx, 4)*begin_dy + -0.00118454 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2)*begin_dy + 724.633 *begin_dx*lens_ipow(begin_dy, 8) + 4224.53 *lens_ipow(begin_dx, 5)*lens_ipow(begin_dy, 4) + 3.62434e-07 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 3) + -2.16249e-11 *begin_x*lens_ipow(begin_y, 8) + -1.4221e-06 *lens_ipow(begin_x, 6)*lens_ipow(begin_dx, 3) + -8.27332e-06 *lens_ipow(begin_x, 5)*begin_y*lens_ipow(begin_dx, 2)*begin_dy*begin_lambda + -3.00783 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 9) + 1.21774 *begin_x*lens_ipow(begin_lambda, 10) + 1.72793e-07 *begin_x*lens_ipow(begin_y, 6)*lens_ipow(begin_dy, 4) + 2.52154e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 8)*begin_dx + 5.96935e-10 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -2.06004e-12 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 4) + -2.75857e-13 *lens_ipow(begin_x, 9)*lens_ipow(begin_y, 2) + -1.06103e-13 *lens_ipow(begin_x, 11);
    out[1] =  + -0.00199184  + 8.94503 *begin_dy + -1.10429 *begin_y + -7.5425e-05 *begin_x + -0.000846069 *begin_y*begin_dy + 1.66825e-05 *begin_x*begin_y + 18.1098 *lens_ipow(begin_dy, 3) + 18.28 *lens_ipow(begin_dx, 2)*begin_dy + 2.40302 *begin_y*lens_ipow(begin_dy, 2) + 0.75627 *begin_y*lens_ipow(begin_dx, 2) + 0.0934855 *lens_ipow(begin_y, 2)*begin_dy + 0.000529547 *lens_ipow(begin_y, 3) + 1.70325 *begin_x*begin_dx*begin_dy + 0.0520897 *begin_x*begin_y*begin_dx + 0.0459837 *lens_ipow(begin_x, 2)*begin_dy + 0.000626996 *lens_ipow(begin_x, 2)*begin_y + 0.875129 *begin_dy*lens_ipow(begin_lambda, 3) + -0.204195 *begin_y*lens_ipow(begin_lambda, 3) + 0.00243235 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + -0.00323916 *begin_x*lens_ipow(begin_y, 2)*begin_dx*begin_dy + 0.0142823 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 2)*begin_dy + 0.00202604 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dy, 2) + 0.0173782 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 4) + -0.000327487 *lens_ipow(begin_x, 3)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -4.5689e-09 *lens_ipow(begin_x, 6)*begin_y + 2042.55 *lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 3) + -84.6786 *begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 6) + -29.7008 *begin_y*lens_ipow(begin_dx, 8) + -1.34469e-06 *lens_ipow(begin_y, 6)*lens_ipow(begin_dy, 3) + -0.00263861 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 4) + 0.385922 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 7) + 8.01991e-07 *lens_ipow(begin_x, 6)*lens_ipow(begin_dy, 3) + -8.9557e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3) + 1130.87 *lens_ipow(begin_dy, 11) + 1.19261 *begin_y*lens_ipow(begin_lambda, 10) + -1.03792e-13 *lens_ipow(begin_y, 11) + -3.56789e-13 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 9) + 3.05472e-09 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6)*begin_dx*begin_dy + -2.04219e-12 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 7) + -1.53295e-12 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 2)*begin_dy;
    out[2] =  + 7.86275e-06  + -0.243478 *begin_dx + -4.11721e-06 *begin_y + -0.0765328 *begin_x + -5.42849e-05 *begin_y*begin_dx + -1.14125e-06 *begin_x*begin_y + 0.745943 *lens_ipow(begin_dx, 3) + 0.0356698 *begin_y*begin_dx*begin_dy + 0.0016271 *lens_ipow(begin_y, 2)*begin_dx + 0.0921058 *begin_x*lens_ipow(begin_dx, 2) + 0.000988368 *begin_x*begin_y*begin_dy + 5.44348e-05 *begin_x*lens_ipow(begin_y, 2) + 0.00302113 *lens_ipow(begin_x, 2)*begin_dx + 8.4201e-05 *lens_ipow(begin_x, 3) + 0.0051488 *begin_x*lens_ipow(begin_lambda, 3) + 6.27912 *lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 2) + 1.51898 *lens_ipow(begin_dx, 5) + -0.0762077 *begin_y*begin_dx*lens_ipow(begin_dy, 3) + 0.137493 *begin_y*lens_ipow(begin_dx, 3)*begin_dy + -0.00229075 *begin_x*begin_y*lens_ipow(begin_dy, 3) + 9.57394e-05 *lens_ipow(begin_x, 3)*lens_ipow(begin_dy, 2) + 3.76457e-09 *lens_ipow(begin_y, 6)*begin_dx + 0.000856676 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00032041 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 3)*begin_dy + 8.35537e-09 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2)*begin_dx + 0.152491 *begin_dx*lens_ipow(begin_lambda, 7) + -0.00179196 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 7) + -5.32782e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3) + -1.26119e-06 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4) + -1.02772e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 6) + -2.59709e-05 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 5) + -3.95969e-10 *lens_ipow(begin_x, 6)*begin_y*begin_dx*begin_dy + -7.04479e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 7) + -286.853 *lens_ipow(begin_dx, 9)*lens_ipow(begin_dy, 2) + 5.04635e-07 *lens_ipow(begin_y, 6)*lens_ipow(begin_dx, 5) + -7.32037e-15 *begin_x*lens_ipow(begin_y, 10) + -1.62897e-07 *lens_ipow(begin_x, 5)*lens_ipow(begin_lambda, 6) + 2.40857e-12 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 3)*begin_dy + -2.66271e-14 *lens_ipow(begin_x, 9)*lens_ipow(begin_y, 2) + 2.37112e-13 *lens_ipow(begin_x, 10)*begin_dx;
    out[3] =  + -5.73891e-05  + -0.265612 *begin_dy + -0.0768949 *begin_y + -2.7567e-06 *begin_x + -1.17794e-05 *begin_y*begin_dy + 1.12368 *lens_ipow(begin_dy, 3) + 1.04884 *lens_ipow(begin_dx, 2)*begin_dy + 0.101074 *begin_y*lens_ipow(begin_dy, 2) + 0.0241024 *begin_y*lens_ipow(begin_dx, 2) + 0.00328513 *lens_ipow(begin_y, 2)*begin_dy + 8.88068e-05 *lens_ipow(begin_y, 3) + 0.0731026 *begin_x*begin_dx*begin_dy + 0.00128435 *begin_x*begin_y*begin_dx + 0.00143947 *lens_ipow(begin_x, 2)*begin_dy + 0.000117865 *lens_ipow(begin_x, 2)*begin_y + 0.815111 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 3) + 0.00719822 *begin_y*lens_ipow(begin_lambda, 4) + 0.00140733 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*begin_dy + 4.93495e-05 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 2) + 0.474821 *lens_ipow(begin_dy, 7) + 0.00643115 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 4)*begin_dy + -1.2643e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4)*begin_dy + -1.22235e-05 *lens_ipow(begin_x, 3)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -2.03569e-10 *lens_ipow(begin_x, 6)*begin_y + -1.8128e-11 *lens_ipow(begin_y, 8)*begin_dy + -0.0156034 *begin_x*begin_dx*lens_ipow(begin_dy, 7) + -2.52922e-11 *begin_x*lens_ipow(begin_y, 7)*begin_dx + 1.91003e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*begin_dy + -1.15918e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 4) + 0.000104055 *lens_ipow(begin_x, 3)*begin_dx*begin_dy*lens_ipow(begin_lambda, 4) + 0.582159 *begin_dy*lens_ipow(begin_lambda, 10) + -0.000865277 *lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 2) + -1.5862e-07 *lens_ipow(begin_y, 5)*lens_ipow(begin_lambda, 6) + 9.24896e-08 *lens_ipow(begin_y, 6)*lens_ipow(begin_dy, 5) + -5.65095e-15 *lens_ipow(begin_y, 11) + -7.85127e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_lambda, 8) + -2.8805e-14 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 9) + 2.6598e-06 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dx, 6) + 3.6261e-07 *lens_ipow(begin_x, 6)*lens_ipow(begin_dy, 5) + -7.14886e-14 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 5);
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
    domega2_dx0[0][0] =  + -0.0765328  + -1.14125e-06 *begin_y + 0.0921058 *lens_ipow(begin_dx, 2) + 0.000988368 *begin_y*begin_dy + 5.44348e-05 *lens_ipow(begin_y, 2) + 0.00604227 *begin_x*begin_dx + 0.000252603 *lens_ipow(begin_x, 2) + 0.0051488 *lens_ipow(begin_lambda, 3) + -0.00229075 *begin_y*lens_ipow(begin_dy, 3) + 0.000287218 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + 0.000856676 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.000640821 *begin_x*begin_y*lens_ipow(begin_dx, 3)*begin_dy + 3.34215e-08 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 2)*begin_dx + -1.06556e-05 *begin_x*lens_ipow(begin_y, 3)*begin_dx*lens_ipow(begin_dy, 3) + -3.78356e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4) + -3.08317e-11 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 6) + -0.000103884 *lens_ipow(begin_x, 3)*lens_ipow(begin_dx, 5) + -2.37582e-09 *lens_ipow(begin_x, 5)*begin_y*begin_dx*begin_dy + -7.04479e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 7) + -7.32037e-15 *lens_ipow(begin_y, 10) + -8.14486e-07 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 6) + 1.686e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 3)*begin_dy + -2.39644e-13 *lens_ipow(begin_x, 8)*lens_ipow(begin_y, 2) + 2.37112e-12 *lens_ipow(begin_x, 9)*begin_dx;
    domega2_dx0[0][1] =  + -4.11721e-06  + -5.42849e-05 *begin_dx + -1.14125e-06 *begin_x + 0.0356698 *begin_dx*begin_dy + 0.00325421 *begin_y*begin_dx + 0.000988368 *begin_x*begin_dy + 0.00010887 *begin_x*begin_y + -0.0762077 *begin_dx*lens_ipow(begin_dy, 3) + 0.137493 *lens_ipow(begin_dx, 3)*begin_dy + -0.00229075 *begin_x*lens_ipow(begin_dy, 3) + 2.25874e-08 *lens_ipow(begin_y, 5)*begin_dx + 0.00171335 *begin_x*begin_y*lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + -0.00032041 *lens_ipow(begin_x, 2)*lens_ipow(begin_dx, 3)*begin_dy + 1.67107e-08 *lens_ipow(begin_x, 4)*begin_y*begin_dx + -0.00358393 *begin_y*lens_ipow(begin_dx, 7) + -1.59834e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*begin_dx*lens_ipow(begin_dy, 3) + -2.52237e-06 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 4) + -6.16634e-11 *lens_ipow(begin_x, 3)*lens_ipow(begin_y, 5) + -3.95969e-10 *lens_ipow(begin_x, 6)*begin_dx*begin_dy + -0.000140896 *begin_x*begin_y*lens_ipow(begin_lambda, 7) + 3.02781e-06 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 5) + -7.32037e-14 *begin_x*lens_ipow(begin_y, 9) + 7.22571e-12 *lens_ipow(begin_x, 7)*lens_ipow(begin_y, 2)*begin_dy + -5.32542e-14 *lens_ipow(begin_x, 9)*begin_y;
    domega2_dx0[1][0] =  + -2.7567e-06  + 0.0731026 *begin_dx*begin_dy + 0.00128435 *begin_y*begin_dx + 0.00287893 *begin_x*begin_dy + 0.000235731 *begin_x*begin_y + 0.0128623 *begin_x*lens_ipow(begin_dx, 4)*begin_dy + -2.52861e-09 *begin_x*lens_ipow(begin_y, 4)*begin_dy + -3.66705e-05 *lens_ipow(begin_x, 2)*begin_y*begin_dx*lens_ipow(begin_dy, 2) + -1.22142e-09 *lens_ipow(begin_x, 5)*begin_y + -0.0156034 *begin_dx*lens_ipow(begin_dy, 7) + -2.52922e-11 *lens_ipow(begin_y, 7)*begin_dx + 3.82006e-05 *begin_x*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 4)*begin_dy + -2.31835e-06 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dy, 4) + 0.000312166 *lens_ipow(begin_x, 2)*begin_dx*begin_dy*lens_ipow(begin_lambda, 4) + -0.000157025 *begin_x*begin_y*lens_ipow(begin_lambda, 8) + -5.76099e-14 *begin_x*lens_ipow(begin_y, 9) + 1.06392e-05 *lens_ipow(begin_x, 3)*begin_y*lens_ipow(begin_dx, 6) + 2.17566e-06 *lens_ipow(begin_x, 5)*lens_ipow(begin_dy, 5) + -4.28932e-13 *lens_ipow(begin_x, 5)*lens_ipow(begin_y, 5);
    domega2_dx0[1][1] =  + -0.0768949  + -1.17794e-05 *begin_dy + 0.101074 *lens_ipow(begin_dy, 2) + 0.0241024 *lens_ipow(begin_dx, 2) + 0.00657027 *begin_y*begin_dy + 0.00026642 *lens_ipow(begin_y, 2) + 0.00128435 *begin_x*begin_dx + 0.000117865 *lens_ipow(begin_x, 2) + 0.00719822 *lens_ipow(begin_lambda, 4) + 0.00281466 *begin_y*lens_ipow(begin_dx, 2)*begin_dy + 0.000148048 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -5.05721e-09 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + -1.22235e-05 *lens_ipow(begin_x, 3)*begin_dx*lens_ipow(begin_dy, 2) + -2.03569e-10 *lens_ipow(begin_x, 6) + -1.45024e-10 *lens_ipow(begin_y, 7)*begin_dy + -1.77045e-10 *begin_x*lens_ipow(begin_y, 6)*begin_dx + 3.82006e-05 *lens_ipow(begin_x, 2)*begin_y*lens_ipow(begin_dx, 4)*begin_dy + -3.47753e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dy, 4) + -0.00259583 *lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 6)*lens_ipow(begin_dy, 2) + -7.93099e-07 *lens_ipow(begin_y, 4)*lens_ipow(begin_lambda, 6) + 5.54938e-07 *lens_ipow(begin_y, 5)*lens_ipow(begin_dy, 5) + -6.21605e-14 *lens_ipow(begin_y, 10) + -7.85127e-05 *lens_ipow(begin_x, 2)*lens_ipow(begin_lambda, 8) + -2.59245e-13 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 8) + 2.6598e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 6) + -3.57443e-13 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 4);
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
  }
  if(out[0]*out[0]+out[1]*out[1] > lens_outer_pupil_radius*lens_outer_pupil_radius) error |= 16;
/* fresnel evaluation:
const float begin_x = sensor[0];
const float begin_y = sensor[1];
const float begin_dx = sensor[2];
const float begin_dy = sensor[3];
const float begin_lambda = sensor[4];
if(error==0)
  out[4] =  + 0.0939579  + 0.283998 *begin_lambda + 5.69737e-06 *begin_y + -1.24655e-06 *begin_x + -0.015335 *lens_ipow(begin_dy, 2) + -0.0158688 *lens_ipow(begin_dx, 2) + -6.98146e-05 *lens_ipow(begin_y, 2) + -9.2267e-05 *lens_ipow(begin_x, 2) + -0.221625 *lens_ipow(begin_lambda, 3) + -0.0034587 *begin_y*begin_dy*begin_lambda + -4.61026e-08 *lens_ipow(begin_y, 3) + -0.00403876 *begin_x*begin_dx*begin_lambda + 6.62396e-07 *lens_ipow(begin_x, 2)*begin_dy + -0.603043 *lens_ipow(begin_dx, 2)*lens_ipow(begin_dy, 2) + 0.000666051 *begin_x*begin_y*begin_dx*begin_dy + 0.000134754 *lens_ipow(begin_x, 2)*lens_ipow(begin_dy, 2) + -1.08569 *lens_ipow(begin_dy, 6) + -1.11828 *lens_ipow(begin_dx, 6) + 2.37597e-06 *lens_ipow(begin_y, 4)*lens_ipow(begin_dy, 2) + -4.13167e-09 *lens_ipow(begin_y, 6) + 5.51156e-06 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 2)*lens_ipow(begin_dx, 2) + -1.745e-07 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 3)*begin_dy + -1.32095e-08 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 4) + 2.32559e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_dx, 2) + -1.56762e-08 *lens_ipow(begin_x, 4)*lens_ipow(begin_y, 2) + -0.0863006 *lens_ipow(begin_dy, 2)*lens_ipow(begin_lambda, 5) + -0.121254 *lens_ipow(begin_dx, 2)*lens_ipow(begin_lambda, 5) + -9.47174e-05 *lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 5) + -3.26731e-07 *lens_ipow(begin_y, 5)*lens_ipow(begin_dx, 2)*begin_dy + 2.14954e-08 *lens_ipow(begin_x, 5)*begin_y*begin_dx*begin_dy + -2.56196e-11 *lens_ipow(begin_x, 8) + 0.143315 *begin_x*begin_dx*lens_ipow(begin_dy, 4)*lens_ipow(begin_lambda, 3) + -1.35581e-06 *lens_ipow(begin_x, 4)*lens_ipow(begin_lambda, 5) + -0.000360361 *begin_x*lens_ipow(begin_y, 3)*lens_ipow(begin_dx, 3)*lens_ipow(begin_dy, 3) + 7.13475e-06 *lens_ipow(begin_x, 4)*begin_y*lens_ipow(begin_dx, 4)*begin_dy + -6.57953e-13 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 4) + 0.448391 *lens_ipow(begin_lambda, 11) + -7.52408e-14 *lens_ipow(begin_y, 10)*begin_lambda + -5.61273e-13 *lens_ipow(begin_x, 2)*lens_ipow(begin_y, 8)*begin_lambda + -9.58858e-11 *lens_ipow(begin_x, 6)*lens_ipow(begin_y, 2)*lens_ipow(begin_lambda, 3);
else
  */
  out[4] = 0.0;
  return error;
}

lens_init(0);
ROOT_NODE.addEventListener("mousedown", handle_lens_event);

