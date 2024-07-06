import {
  Drawer as MuiDrawer,
  Typography,
} from '@mui/material';
import { makeStyles } from '@mui/styles';
import { Dispatch, SetStateAction, useCallback } from 'react';

const useStyles = makeStyles(
  () => ({
    drawer: {
      width: 380,
    },
    drawerPaper: {
      width: 380,
      color: '#fff',
      padding: 50,
      backgroundSize: 'cover',
      backgroundPosition: 'center',
      backgroundRepeat: 'no-repeat',
    },
  })
) as any;

const textStyles = {
  color: '#fff',
  lineHeight: 1.6
}

const Drawer = ({
  open,
  onClose,
  data
}: {
  open: boolean
  onClose: Dispatch<SetStateAction<boolean>>
  data: any
}) => {
  const classes = useStyles();

  const handleClose = useCallback(
    () => {
      onClose(false)
    }, [onClose]
  )

  const drawerStyle = {
    backgroundImage: `url(${data?.image})`,
  };

  return (
    <MuiDrawer
      open={open}
      onClose={handleClose}
      classes={{
        paper: classes.drawerPaper,
      }}
      PaperProps={{
        style: drawerStyle
      }}
    >
      <Typography variant="h4" gutterBottom sx={textStyles}>
        { data?.title }
      </Typography>
      <Typography variant="body1" sx={textStyles}>
        { data?.content }
      </Typography>
    </MuiDrawer>
  );
};

export default Drawer;
