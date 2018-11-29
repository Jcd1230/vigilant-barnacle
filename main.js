let canvas = document.getElementById("canvas");
const W = 768;
const H = 480;
canvas.width = W;
canvas.height = H;
let ctx = canvas.getContext('2d');

ctx.fillStyle = 'chartreuse';
ctx.strokeStyle = 'black'

// Set line width
ctx.lineWidth = 10;

// Wall
ctx.strokeRect(75, 140, 150, 110);

// Door
ctx.fillRect(130, 190, 40, 60);

// Roof
ctx.moveTo(50, 140);
ctx.lineTo(150, 60);
ctx.lineTo(250, 140);
ctx.closePath();
ctx.stroke();

var particles = [];

var p_x = [];
var p_y = [];
var p_r = [];
var p_g = [];
var p_b = [];
var p_size = [];
var p_vx = [];
var p_vy = [];
var p_frame = [];

function reset_particle(i, start_frame) {
	p_x[i] = W/2 + Math.random()*50-25,
	p_y[i] = H,
	p_r[i] = 255,
	p_g[i] = 255,
	p_b[i] = 0,
	p_size[i] = 1,
	p_vx[i] = Math.random()*16 - 8,
	p_vy[i] = Math.random()*8-32,
	p_frame[i] = start_frame || (Math.random()*60)|0
}

const PARTICLES = 100000
for (var i = 0; i < PARTICLES; i++) {
	reset_particle(i);
}
ctx.imageSmoothingEnabled = false;
ctx.webkitImageSmoothingEnabled = false;
var cur_frame = 0;
var curtime = performance.now();
var slider = document.getElementById("slider");
var draw
draw = function() {
	++cur_frame;
	ctx.clearRect(0, 0, W, H);
	ctx.fillStyle = 'black';
	var particles_shown = slider.value;
	for (var i = 0; i < particles_shown; i++) {
		if (cur_frame < p_frame[i]) { continue };

		var oldx = p_x[i];
		var oldy = p_y[i];
		p_x[i] += p_vx[i];
		p_y[i] += p_vy[i];

		if (p_y[i] > H) {
			reset_particle(i, cur_frame);
		}

		p_size[i] *= 0.97;

		p_r[i] *= 0.95;
		p_g[i] *= 0.9;

		p_vy[i] += 1;

		ctx.beginPath();
		ctx.lineWidth = p_size[i];
		//ctx.strokeStyle = 'rgb('+p_r[i]+','+p_g[i]+','+p_b[i]+')';
		ctx.moveTo(oldx, oldy)
		ctx.lineTo(p_x[i], p_y[i]);
		ctx.stroke()
		ctx.closePath();

	};
	var now = performance.now();
	ctx.fillText(((now - curtime)|0) + 'ms', 5, 10);
	ctx.fillText(particles_shown + ' particles', 5, 25);
	curtime = now;
	window.requestAnimationFrame(draw);
}
window.requestAnimationFrame(draw);