'use client'

import { useState } from "react";
import Loading from "@/app/components/loading";
import Map from "@/app/components/map";
import Drawer from "@/app/components/drawer";

const Exemplo = () => {
  const [loading, setLoading] = useState(true);
  const [drawer, setDrawer] = useState(false);
  const [data, setData] = useState({});

  return (
    <>
      <Loading
        loading={loading}
      />
      <Map
        setLoading={setLoading}
        setDrawer={setDrawer}
        setData={setData}
      />
      <Drawer
        data={data}
        open={drawer}
        onClose={setDrawer}
      />
    </>
  )
}

export default Exemplo