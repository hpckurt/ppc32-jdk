package com.sun.corba.se.spi.activation;

/**
* com/sun/corba/se/spi/activation/ServerHolder.java .
* Generated by the IDL-to-Java compiler (portable), version "3.2"
* from /var/lib/jenkins/ws/workspace/zulu8/linux/ppchf/c1/build/generic/ca/release/crossbuild/zulu8-emb-dev/corba/src/share/classes/com/sun/corba/se/spi/activation/activation.idl
* Monday, August 3, 2020 4:28:24 PM MSK
*/


/** Server callback API, passed to Activator in active method.
    */
public final class ServerHolder implements org.omg.CORBA.portable.Streamable
{
  public com.sun.corba.se.spi.activation.Server value = null;

  public ServerHolder ()
  {
  }

  public ServerHolder (com.sun.corba.se.spi.activation.Server initialValue)
  {
    value = initialValue;
  }

  public void _read (org.omg.CORBA.portable.InputStream i)
  {
    value = com.sun.corba.se.spi.activation.ServerHelper.read (i);
  }

  public void _write (org.omg.CORBA.portable.OutputStream o)
  {
    com.sun.corba.se.spi.activation.ServerHelper.write (o, value);
  }

  public org.omg.CORBA.TypeCode _type ()
  {
    return com.sun.corba.se.spi.activation.ServerHelper.type ();
  }

}
