/*
 * Copyright (c) 1998, 2015, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

package javax.swing;

import java.beans.BeanDescriptor;
import java.beans.PropertyDescriptor;
import java.awt.Image;

import sun.swing.BeanInfoUtils;

/**
 * Descriptive information about the JMenu class for Java 
 * Beans application builders.  This BeanInfo class provides descriptions
 * of each property, of the bean itself, it indicates which
 * JMenu properties are bound, and it provides other
 * information and icons useful to builders.
 * 
 * @author Auto-Generated Source Code
 */

public class JMenuBeanInfo extends javax.swing.SwingBeanInfoBase {
    private static final Class classJMenu = javax.swing.JMenu.class;

    /**
     * @return a JMenu BeanDescriptor
     */
    public BeanDescriptor getBeanDescriptor() {
        return BeanInfoUtils.createBeanDescriptor(classJMenu,
                                                  new Object[] {
                BeanInfoUtils.PREFERRED, Boolean.TRUE,
                              "isContainer", Boolean.TRUE,
                 
                    BeanInfoUtils.SHORTDESCRIPTION, "A popup window containing menu items displayed in a menu bar."
        });
    }


    /**
     * Create a JMenu PropertyDescriptor.  This is just an internal
     * convenience method that allows one to leave the JMenu.class
     * argument out of the createPropertyDescriptor() class in the 
     * getPropertyDescriptors() method below.
     * 
     * @param name the name of the property
     * @param args an array java.beans.PropertyDescriptor property names and values
     * @return a JMenu PropertyDescriptor.
     * @see BeanInfoUtils#createPropertyDescriptor
     */
    private PropertyDescriptor createPropertyDescriptor(String name, Object[] args) {
        return BeanInfoUtils.createPropertyDescriptor(classJMenu, name, args);
    }


    /**
     * This method returns a list of bean PropertyDescriptors, one for each public
     * property in JMenu.  The first property is the "default" property.
     *
     * @return a complete list of bean PropertyDescriptors for JMenu
     * @see SwingBeanInfo
     * @see java.beans.BeanInfo#getDefaultPropertyIndex
     */
    public PropertyDescriptor[] getPropertyDescriptors() {
         
        return new PropertyDescriptor[] {
            
             createPropertyDescriptor("UIClassID", new Object[] {
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "UIClassID",
               }
             ),
             
             createPropertyDescriptor("accessibleContext", new Object[] {
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "accessibleContext",
               }
             ),
             
             createPropertyDescriptor("component", new Object[] {
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "component",
               }
             ),
             
             createPropertyDescriptor("delay", new Object[] {
                            sun.swing.BeanInfoUtils.BOUND, Boolean.FALSE,
                           sun.swing.BeanInfoUtils.EXPERT, Boolean.TRUE,
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "The delay between menu selection and making the popup menu visible ",
               }
             ),
             
             createPropertyDescriptor("itemCount", new Object[] {
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "itemCount",
               }
             ),
             
             createPropertyDescriptor("menuComponentCount", new Object[] {
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "menuComponentCount",
               }
             ),
             
             createPropertyDescriptor("menuComponents", new Object[] {
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "menuComponents",
               }
             ),
             
             createPropertyDescriptor("menuListeners", new Object[] {
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "menuListeners",
               }
             ),
             
             createPropertyDescriptor("popupMenu", new Object[] {
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "popupMenu",
               }
             ),
             
             createPropertyDescriptor("popupMenuVisible", new Object[] {
                            sun.swing.BeanInfoUtils.BOUND, Boolean.FALSE,
                           sun.swing.BeanInfoUtils.EXPERT, Boolean.TRUE,
                           sun.swing.BeanInfoUtils.HIDDEN, Boolean.TRUE,
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "The popup menu's visibility ",
               }
             ),
             
             createPropertyDescriptor("selected", new Object[] {
                            sun.swing.BeanInfoUtils.BOUND, Boolean.FALSE,
                           sun.swing.BeanInfoUtils.EXPERT, Boolean.TRUE,
                           sun.swing.BeanInfoUtils.HIDDEN, Boolean.TRUE,
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "When the menu is selected, its popup child is shown. ",
               }
             ),
             
             createPropertyDescriptor("subElements", new Object[] {
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "subElements",
               }
             ),
             
             createPropertyDescriptor("tearOff", new Object[] {
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "tearOff",
               }
             ),
             
             createPropertyDescriptor("topLevelMenu", new Object[] {
                 sun.swing.BeanInfoUtils.SHORTDESCRIPTION, "topLevelMenu",
               }
             )
             
        };
    }


    /**
     * @return an icon of the specified kind for JMenu
     */
    public Image getIcon(final int kind) {
        Image i;
        switch (kind){
            case ICON_COLOR_32x32:
                i = loadStandardImage("beaninfo/images/JMenuColor32.gif");
                return ((i == null) ? loadStandardImage("beaninfo/images/JComponentColor32.gif") : i);
            case ICON_COLOR_16x16:
                i = loadStandardImage("beaninfo/images/JMenuColor16.gif");
                return ((i == null) ? loadStandardImage("beaninfo/images/JComponentColor16.gif") : i);
            case ICON_MONO_32x32:
                i = loadStandardImage("beaninfo/images/JMenuMono32.gif");
                return ((i == null) ? loadStandardImage("beaninfo/images/JComponentMono32.gif") : i);         
            case ICON_MONO_16x16:
                i = loadStandardImage("beaninfo/images/JMenuMono16.gif");
                return ((i == null) ? loadStandardImage("beaninfo/images/JComponentMono16.gif") : i);         
            default:
                return super.getIcon(kind);
        }
    }

    /**
     * This is a utility method to help in loading standard icon images.
     *
     * @param  resourceName A pathname relative to the directory holding the
     *         class file of the current class
     * @return an image object. May be null if the load failed.
     * @see java.beans.SimpleBeanInfo#loadImage(String)
     */
    private Image loadStandardImage(final String resourceName) {
        return java.security.AccessController.doPrivileged(
                (java.security.PrivilegedAction<Image>) () -> loadImage(resourceName));
    }
}


