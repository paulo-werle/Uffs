// components/Loading.js
import { Backdrop, CircularProgress } from '@mui/material';
import { makeStyles } from '@mui/styles';

const useStyles = makeStyles(
  () => ({
    backdrop: {
      zIndex: 9999,
      color: '#fff',
    },
  })
) as any;

const Loading = ({
  loading
}: {
  loading: boolean
}) => {
  const classes = useStyles();

  return (
    <Backdrop className={classes.backdrop} open={loading}>
      <CircularProgress color="inherit" />
    </Backdrop>
  );
}

export default Loading;
