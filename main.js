let canvas = document.getElementById("canvas");
const W = 768;
const H = 480;
canvas.width = W;
canvas.height = H;
let gl = canvas.getContext('webgl');

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

let vPosition = gl.getAttribLocation(program, "vPosition");
let positionBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array([1,1,1,1, -1,-1,-1,1]), gl.STATIC_DRAW);
gl.vertexAttribPointer(vPosition, 4, gl.FLOAT, false, 0, 0);
gl.enableVertexAttribArray(vPosition);
gl.drawArrays(gl.LINES, 0, 2);

	if (false) {

const PARTICLES = 100000
for (var i = 0; i < PARTICLES; i++) {
	reset_particle(i);
}
var cur_frame = 0;
var curtime = performance.now();
var slider = document.getElementById("slider");
var draw
draw = function() {
	++cur_frame;
	gl.clearColor(1.0, 1.0, 1.0);
	gl.clear(gl.COLOR_BUFFER_BIT);
	var particles_shown = slider.value;
	for (var i = 0; i < particles_shown; i++) {
		if (cur_frame < p_frame[i]) { continue };

		var oldx = p_x[i];
		var oldy = p_y[i];
		p_x[i] += p_vx[i];
		p_y[i] += p_vy[i];

		if (p_y[i] > H) {
			reset_particle(i, cur_frame);
			oldx = p_x[i];
			oldy = p_y[i];
		}

		p_size[i] *= 0.97;

		p_r[i] *= 0.95;
		p_g[i] *= 0.9;

		p_vy[i] += 1;

		gl.drawArrays(gl.LINES, 0, 2);
		//ctx.beginPath();
		//ctx.lineWidth = p_size[i];
		//ctx.moveTo(oldx, oldy)
		//ctx.lineTo(p_x[i], p_y[i]);
		//ctx.stroke()
		//ctx.closePath();

	};
	var now = performance.now();
	//ctx.fillText(((now - curtime)|0) + 'ms', 5, 10);
	//ctx.fillText(particles_shown + ' particles', 5, 25);
	curtime = now;
	window.requestAnimationFrame(draw);
}

window.requestAnimationFrame(draw);


}
