'use client'

import { Dispatch, SetStateAction, useLayoutEffect } from "react";
import { ThreeJs3DMap } from "three-js-map";

const Map = ({
  setLoading,
  setDrawer,
  setData,
}: {
  setLoading: Dispatch<SetStateAction<boolean>>
  setDrawer: Dispatch<SetStateAction<boolean>>
  setData: Dispatch<SetStateAction<boolean>>
}) => {
  useLayoutEffect(
    () => {
      const threeJs3DMap = ThreeJs3DMap({
        development: true,
        container: {
          cameraPosition: {
            x: 0,
            y: 5,
            z: 2
          },
        },
        control: {
          minDistance: 2,
          maxDistance: 10,
          minPan: { x: -10, z: -10 },
          maxPan: { x:  10, z:  10 },
        },
        light: {
          color: 0xffffff,
          position: { x: 0, y: 10, z: 0 },
          intensity: 1,
        },
        helper: {
          size: 10 * 4
        },
        map: {
          path: '/assets/maps/map1.glb',
          scale: { x: 10, y: 10, z: 10 }
        },
        objects: [
          {
            path: '/assets/buildings/build1.glb',
            position: { x: 5.7, y: 0.9, z: -9.8 },
            scale: { x: 0.01, y: 0.01, z: 0.01 },
            clickDistance: 3,
            clickData: {
              title: 'Posto de Comunicação Abandonado',
              image: '/assets/buildings/build1.png',
              content: `
                Sobre a mais alta montanha da Floresta Perdida ergue-se o Posto de Comunicação da Montanha Solitária, uma estrutura modesta de madeira e metal perdida entre as copas das árvores. A pequena antena de rádio se estende para o céu, captando e enviando sinais que conectam aqueles que habitam a floresta com o mundo exterior.
                Construído pelos primeiros exploradores que desbravaram a região, o posto serve não apenas como um ponto de comunicação essencial, mas também como um farol de esperança para os perdidos na vastidão verde da floresta. Os guardiões do posto são uma pequena equipe de técnicos e comunicadores, cujo compromisso é manter vivo o elo entre os habitantes da floresta e o resto do mundo.
                Em dias claros, a vista do topo da montanha permite vislumbrar além das fronteiras da floresta, revelando planícies distantes e o brilho das cidades modernas. À noite, as estrelas se refletem nas antenas, como se a própria estrutura estivesse sussurrando segredos para o universo.
              `
            },
            onClickCallback: (data, model, intersection, event) => {
              setData(data)
              setDrawer(true)

              console.log(data, model, intersection, event)
            }
          }, {
            path: '/assets/buildings/build2.glb',
            position: { x: 0.45, y: -0.63, z: -2.85 },
            scale: { x: 0.01, y: 0.01, z: 0.01 },
            clickDistance: 3,
            clickData: {
              title: 'Armazém da Floresta Perdida',
              image: '/assets/buildings/build2.png',
              content: `
                No coração de uma densa floresta, onde os raios de sol mal alcançam o chão coberto de musgo, encontra-se o misterioso Armazém da Floresta Perdida. Escondido entre árvores centenárias e caminhos sinuosos, este antigo armazém não pertence a nenhum mapa conhecido pelos habitantes locais. Dizem as lendas que foi construído por uma civilização perdida há séculos, cujos descendentes ainda guardam segredos profundos e conhecimentos ancestrais.
                Seus muros de pedra cinzenta são adornados com hera e líquens, dando a impressão de que o próprio tempo se deteve ali. Dentro do armazém, prateleiras de madeira polida sustentam frascos de vidro contendo poções mágicas, ervas raras que brilham suavemente à luz fraca que penetra pelas pequenas janelas.
                O guardião do armazém é um velho sábio, de olhos brilhantes e longas barbas brancas, cuja sabedoria é procurada por aqueles que buscam curas para males incuráveis ou artefatos de poder perdidos no tempo. Ele vive em harmonia com a floresta e seus habitantes mágicos, cuidando tanto dos segredos do armazém quanto dos mistérios que envolvem a própria floresta.
              `
            },
            onClickCallback: (data, model, intersection, event) => {
              setData(data)
              setDrawer(true)

              console.log(data, model, intersection, event)
            }
          }
        ],
        onLoadComplete: () => {
          setLoading(false)
        }
      })

      console.log(threeJs3DMap)
    }, [
      setLoading,
      setData,
      setDrawer
    ]
  )

  return (
    <canvas id="three-js-3d-map"></canvas>
  )
}

export default Map