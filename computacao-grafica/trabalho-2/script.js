import * as THREE from 'three'
import { FontLoader } from 'three/addons/loaders/FontLoader.js'
import { ParametricGeometry } from 'three/addons/geometries/ParametricGeometry.js'
import { TextGeometry } from 'three/addons/geometries/TextGeometry.js'

function main() {
  const canvas = document.querySelector('#c')
  const renderer = new THREE.WebGLRenderer({ antialias: true, canvas })

  const fov = 40
  const aspect = 2
  const near = 0.1
  const far = 1000

  const camera = new THREE.PerspectiveCamera(fov, aspect, near, far)
  camera.position.z = 120

  const scene = new THREE.Scene()
  scene.background = new THREE.Color(0xaaaaaa)

  {
    const color = 0xffffff
    const intensity = 3
    const light = new THREE.DirectionalLight(color, intensity)
    light.position.set(-1, 2, 4)
    scene.add(light)
  }

  {
    const color = 0xffffff
    const intensity = 3
    const light = new THREE.DirectionalLight(color, intensity)
    light.position.set(1, -2, -4)
    scene.add(light)
  }

  const objects = []
  const spread = 15

  function addObject(x, y, obj) {
    obj.position.x = x * spread
    obj.position.y = y * spread

    scene.add(obj)
    objects.push(obj)
  }

  function createMaterial() {
    const material = new THREE.MeshPhongMaterial({
      side: THREE.DoubleSide,
    })

    const hue = Math.random()
    const saturation = 1
    const luminance = 0.5
    material.color.setHSL(hue, saturation, luminance)

    return material
  }

  function addSolidGeometry(x, y, geometry) {
    const mesh = new THREE.Mesh(geometry, createMaterial())
    addObject(x, y, mesh)
  }

  // Objeto 1
  {
    const shape = new THREE.Shape()
    const x = -2.5
    const y = -5
    shape.moveTo(x + 2.5, y + 2.5)
    shape.bezierCurveTo(x + 2.5, y + 2.5, x + 2, y, x, y)
    shape.bezierCurveTo(x - 3, y, x - 3, y + 3.5, x - 3, y + 3.5)
    shape.bezierCurveTo(x - 3, y + 5.5, x - 1.5, y + 7.7, x + 2.5, y + 9.5)
    shape.bezierCurveTo(x + 6, y + 7.7, x + 8, y + 4.5, x + 8, y + 3.5)
    shape.bezierCurveTo(x + 8, y + 3.5, x + 8, y, x + 5, y)
    shape.bezierCurveTo(x + 3.5, y, x + 2.5, y + 2.5, x + 2.5, y + 2.5)

    const extrudeSettings = {
      steps: 2,
      depth: 2,
      bevelEnabled: true,
      bevelThickness: 1,
      bevelSize: 1,
      bevelSegments: 2,
    }

    addSolidGeometry(-2, 2, new THREE.ExtrudeGeometry(shape, extrudeSettings))
  }

  // Objeto 2
  {
    function klein(v, u, target) {
      u *= Math.PI
      v *= 2 * Math.PI
      u = u * 2

      let x
      let z

      if (u < Math.PI) {
        x =
          3 * Math.cos(u) * (1 + Math.sin(u)) +
          2 * (1 - Math.cos(u) / 2) * Math.cos(u) * Math.cos(v)
        z =
          -8 * Math.sin(u) -
          2 * (1 - Math.cos(u) / 2) * Math.sin(u) * Math.cos(v)
      } else {
        x =
          3 * Math.cos(u) * (1 + Math.sin(u)) +
          2 * (1 - Math.cos(u) / 2) * Math.cos(v + Math.PI)
        z = -8 * Math.sin(u)
      }

      const y = -2 * (1 - Math.cos(u) / 2) * Math.sin(v)

      target.set(x, y, z).multiplyScalar(0.75)
    }

    const slices = 25
    const stacks = 25
    addSolidGeometry(2, 2, new ParametricGeometry(klein, slices, stacks))
  }

  // Objeto 3
  {
    const loader = new FontLoader()
    // promisify font loading
    function loadFont(url) {
      return new Promise((resolve, reject) => {
        loader.load(url, resolve, undefined, reject)
      })
    }

    async function doit() {
      const font = await loadFont(
        'https://threejs.org/examples/fonts/helvetiker_regular.typeface.json'
      )
      const geometry = new TextGeometry('Computacao Grafica', {
        font: font,
        size: 3.0,
        depth: 0.2,
        curveSegments: 12,
        bevelEnabled: true,
        bevelThickness: 0.15,
        bevelSize: 0.3,
        bevelSegments: 5,
      })
      const mesh = new THREE.Mesh(geometry, createMaterial())
      geometry.computeBoundingBox()
      geometry.boundingBox.getCenter(mesh.position).multiplyScalar(-1)

      const parent = new THREE.Object3D()
      parent.add(mesh)

      addObject(0, 0, parent)
    }

    doit()
  }

  // Objeto 4
  {
    const radius = 5
    const tubeRadius = 2
    const radialSegments = 8
    const tubularSegments = 24
    addSolidGeometry(
      -2,
      -2,
      new THREE.TorusGeometry(
        radius,
        tubeRadius,
        radialSegments,
        tubularSegments
      )
    )
  }

  // Objeto 5
  {
    const radius = 3.5
    const tube = 1.5
    const radialSegments = 8
    const tubularSegments = 64
    const p = 2
    const q = 3
    addSolidGeometry(
      2,
      -2,
      new THREE.TorusKnotGeometry(
        radius,
        tube,
        tubularSegments,
        radialSegments,
        p,
        q
      )
    )
  }

  function resizeRendererToDisplaySize(renderer) {
    const canvas = renderer.domElement
    const width = canvas.clientWidth
    const height = canvas.clientHeight
    const needResize = canvas.width !== width || canvas.height !== height
    if (needResize) {
      renderer.setSize(width, height, false)
    }

    return needResize
  }

  function render(time) {
    time *= 0.001

    if (resizeRendererToDisplaySize(renderer)) {
      const canvas = renderer.domElement
      camera.aspect = canvas.clientWidth / canvas.clientHeight
      camera.updateProjectionMatrix()
    }

    objects.forEach((obj, ndx) => {
      const speed = 0.1 + ndx * 0.05
      const rot = time * speed
      obj.rotation.x = rot
      obj.rotation.y = rot
    })

    renderer.render(scene, camera)

    requestAnimationFrame(render)
  }

  requestAnimationFrame(render)
}

main()
