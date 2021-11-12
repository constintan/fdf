# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lajudy <lajudy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 17:15:03 by lajudy            #+#    #+#              #
#    Updated: 2021/11/13 01:05:56 by lajudy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c libft.c map_init.c map_init2.c\
		ft_split.c draw_projections.c\
		ft_atoi.c draw_map.c\
		draw_map_utils.c color_utils.c

HDRS =	fdf.h

PATHTOMLX = minilibx_macos/
PATHTOGNL = gnl/
MLX = ${PATHTOMLX}libmlx.a
GNL = ${PATHTOGNL}libgnl.a

OBJS = 	$(SRCS:.c=.o)

NAME = 	fdf

CC = 	gcc
CFLAGS = -Wall -Wextra -Werror
FRMWRKS = -framework OpenGL -framework AppKit 
RM = 	rm -f

all:	${GNL} ${MLX} ${NAME} 

${GNL}: 
	@echo "Making ${GNL}"
	@make -C ${PATHTOGNL}

${MLX}:
	@echo "Making ${MLX}"
	@make -C ${PATHTOMLX}

$(OBJS):$(HDRS) Makefile

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L${PATHTOGNL} -lgnl -L${PATHTOMLX} -lmlx  ${FRMWRKS} -o $(NAME)

bonus: all

clean:
	${RM} ${OBJS}
	@make -C ${PATHTOGNL} clean
	@make -C ${PATHTOMLX} clean

fclean: clean
	${RM} ${NAME}
	@make -C ${PATHTOGNL} fclean

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS} ${BSRCS}
	norminette -R CheckDefine ${HDRS}

.PHONY: all clean fclean re bonus norm